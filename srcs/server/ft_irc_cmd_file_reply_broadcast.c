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

/*TODO
 * Remove debug
 * */

static void		ft_irc_cmd_file_reply_user(t_env *e, char *us, char *b, int len)
{
	int				i;

	i = 0;
	while (i < e->maxfd)
	{
		if (e->fds[i].type == FD_CLIENT &&
			ft_strcmp(us, e->fds[i].username) == 0)
			ft_send(i, b, (size_t)len, e);
		i++;
	}
}

static int			ft_irc_cmd_file_reply_parse(t_env *e, int cs, t_file *f)
{
	if (f->info.dest[0] == '#')
	{
		ft_irc_cmd_file_reply_chanel(e, cs, f->info.dest,
									 e->fds[cs].buff_len);
		return (1);
	}
	return (0);
	//else
	//	ft_irc_cmd_file_reply_user(e, f->info.dest,
	//							e->fds[cs].buffer, e->fds[cs].buff_len);
}

static void		ft_irc_cmd_file_reply_split(t_env *e, int cs, void *ptr, int l)
{
	uint64_t		*magic;
	int				new_len;

	magic = (uint64_t*)ptr;
	new_len = e->fds[cs].buff_len - l;
	if (magic[0] == MH_MAGIC_FILE || magic[0] == MH_MAGIC_MTU)
	{
		printf("next is magic0\n");
		ft_memcpy(BF(cs), (void*)&magic[0], (size_t)new_len);
		ft_bzero(&BF(cs)[new_len + 1], (size_t)l);
		e->fds[cs].buff_len = new_len;
		ft_irc_cmd_file(e, cs);
	}
	printf("end next magic\n");
}

int				ft_irc_cmd_file_reply_broadcast(t_env *e, int cs, t_file *f)
{
	uint64_t		*magic;
	int				len;

	ft_bzero(f->info.source, CH_LEN + 1);
	ft_strcat(f->info.source, e->fds[cs].username);
	len = (int)(SIZE_SFILE(BUF_SIZE) + f->info.l);
	printf("reply_broadcast: buff_len = %d psize = %d %d/%d\n",e->fds[cs].buff_len , len, f->info.p, f->info.t);
	printf("source: '%s'\n", f->info.source);
	printf("dest: '%s'\n", f->info.dest);
	printf("file_name: '%s'\n", f->info.file_name);
	printf("pklen: '%d'\n", f->info.l);
	if (ft_irc_cmd_file_reply_parse(e, cs, f) == 0)
		return (0);
	if (e->fds[cs].buff_len == len)
		return (1);
	if ((e->fds[cs].buff_len / 2) + 1 > len && f->info.t != f->info.p)
	{
		magic = (uint64_t*)&BF(cs)[len];
		printf("reply_split\n");
		ft_irc_cmd_file_reply_split(e, cs, (void*)magic, len);
	}
	else if ((e->fds[cs].buff_len < len && f->info.t != f->info.p) ||
			(e->fds[cs].buff_len - len > 0 && f->info.t != f->info.p))
	{
		e->fds[cs].tlen = e->fds[cs].buff_len - len;
		if (e->fds[cs].tlen < 0)
		{
			printf("an error was ocured (%d)\n", e->fds[cs].tlen);
			return (1);
		}
		printf("next is truckated, save data (%d)bits\n", e->fds[cs].tlen);
		e->fds[cs].tfile = ft_strnew((size_t)e->fds[cs].tlen);
		ft_memcpy(e->fds[cs].tfile, &BF(cs)[len], (size_t)e->fds[cs].tlen);
	}
	return (1);
}
