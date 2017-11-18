/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_cmd_file_reply_broadcast.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 18:37:51 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/18 13:53:39 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_server.h"

static int		ft_irc_cmd_file_reply_parse(t_env *e, int cs, t_file *f)
{
	if (f->info.dest[0] == '#')
	{
		ft_irc_cmd_file_reply_chanel(e, cs, f->info.dest,
									e->fds[cs].buff_len);
		return (1);
	}
	return (0);
}

static void		ft_irc_cmd_file_reply_split(t_env *e, int cs, void *ptr, int l)
{
	uint64_t		*magic;
	int				new_len;

	magic = (uint64_t*)ptr;
	new_len = e->fds[cs].buff_len - l;
	if (magic[0] == MH_MAGIC_FILE || magic[0] == MH_MAGIC_MTU)
	{
		ft_memcpy(BF(cs), (void*)&magic[0], (size_t)new_len);
		ft_bzero(&BF(cs)[new_len + 1], (size_t)l);
		e->fds[cs].buff_len = new_len;
		ft_irc_cmd_file(e, cs);
	}
}

int				ft_irc_cmd_file_reply_broadcast(t_env *e, int cs, t_file *f)
{
	uint64_t		*magic;
	int				len;

	ft_bzero(f->info.source, CH_LEN + 1);
	ft_strcat(f->info.source, e->fds[cs].username);
	len = (int)(SIZE_SFILE(BUF_SIZE) + f->info.l);
	if (ft_irc_cmd_file_reply_parse(e, cs, f) == 0)
		return (0);
	if (e->fds[cs].buff_len == len)
		return (1);
	if ((e->fds[cs].buff_len / 2) + 1 > len && f->info.t != f->info.p)
	{
		magic = (uint64_t*)&BF(cs)[len];
		ft_irc_cmd_file_reply_split(e, cs, (void*)magic, len);
	}
	else if ((e->fds[cs].buff_len < len && f->info.t != f->info.p) ||
			(e->fds[cs].buff_len - len > 0 && f->info.t != f->info.p))
	{
		e->fds[cs].tlen = e->fds[cs].buff_len - len;
		if (e->fds[cs].tlen < 0)
			return (1);
		e->fds[cs].tfile = ft_strnew((size_t)e->fds[cs].tlen);
		ft_memcpy(e->fds[cs].tfile, &BF(cs)[len], (size_t)e->fds[cs].tlen);
	}
	return (1);
}
