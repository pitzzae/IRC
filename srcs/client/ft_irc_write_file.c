/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_write_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 17:24:01 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/18 15:41:27 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_client.h"

static void	ft_irc_write_file_split(t_env *e, int cs, t_file *f)
{
	uint64_t		*magic;
	int				len;
	int				new_len;

	len = (int)(SIZE_SFILE(BUF_SIZE) + f->info.l);
	new_len = BL(cs) + len;
	magic = (uint64_t*)&RB(cs)[len];
	if (magic[0] == MH_MAGIC_FILE || magic[0] == MH_MAGIC_MTU)
	{
		ft_memcpy(RB(cs), (void*)&magic[0], (size_t)new_len);
		ft_bzero(&RB(cs)[new_len], (size_t)len);
		e->fds[cs].r = new_len;
		ft_irc_parse_is_file(e, cs, new_len);
	}
}

static void	ft_irc_write_file_trunck(t_env *e, int cs, int len)
{
	e->fds[cs].tlen = e->fds[cs].r - len;
	if (e->fds[cs].tlen < 0)
		return ;
	e->fds[cs].tfile = ft_strnew((size_t)e->fds[cs].tlen);
	ft_memcpy(e->fds[cs].tfile, &e->fds[cs].buf_read[len],
			(size_t)e->fds[cs].tlen);
}

int			ft_irc_write_file(t_env *e, int cs, t_file *f)
{
	int				len;

	len = (int)(SIZE_SFILE(BUF_SIZE) + f->info.l);
	if (f->info.p == 1)
		ft_irc_create_file(e, f);
	if (e->fds[cs].r >= len)
		ft_irc_cat_infile(e, cs, f);
	else
		ft_irc_write_file_trunck(e, cs, len);
	if (f->info.p == f->info.t)
		ft_irc_close_file(e, f);
	if (e->fds[cs].r == len)
		return (1);
	if ((e->fds[cs].r / 2) + 1 > len && f->info.t != f->info.p)
		ft_irc_write_file_split(e, cs, f);
	else if ((e->fds[cs].r < len && f->info.t != f->info.p) ||
			(e->fds[cs].r - len > 0 && f->info.t != f->info.p))
		ft_irc_write_file_trunck(e, cs, len);
	return (1);
}
