/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_write_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 17:24:01 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/16 23:51:10 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_client.h"

static void	ft_irc_write_file_split(t_env *e, int cs, t_file *f)
{
	uint64_t		*magic;
	int				len;
	int				new_len;

	len = (int)(SIZE_SFILE(BUF_SIZE) + f->info.l);
	new_len = BL(cs) - len;
	magic = (uint64_t*)&RB(cs)[len];
	if (magic[0] == MH_MAGIC_FILE || magic[0] == MH_MAGIC_MTU)
	{
		dprintf(7, "next is magic0\n");
		ft_memcpy(RB(cs), (void*)&magic[0], (size_t)new_len);
		ft_bzero(&RB(cs)[new_len], (size_t)len);
		e->fds[cs].r = new_len;
		ft_irc_parse_is_file(e, cs, new_len);
	}
	dprintf(7, "end next magic\n");
}

int			ft_irc_write_file(t_env *e, int cs, t_file *f)
{
	int				len;

	len = (int)(SIZE_SFILE(BUF_SIZE) + f->info.l);
	dprintf(7, "write: buff_len = %d psize = %d %d/%d\n",e->fds[cs].r , len, f->info.p, f->info.t);
	if (f->info.p == 1)
		ft_irc_create_file(e, f);
	ft_irc_cat_infile(e, f);
	if (f->info.p == f->info.t)
		ft_irc_close_file(e, f);
	if (BL(cs) > (int)(SIZE_SFILE(BUF_SIZE) + f->info.l))
		ft_irc_write_file_split(e, cs, f);
	return (1);
}
