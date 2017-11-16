/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_cmd_file_reply_broadcast.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 18:37:51 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/16 21:07:45 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_server.h"

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

static void		ft_irc_cmd_file_reply_chanel(t_env *e, int cs, char *ch, int le)
{
	t_chanel		*c;
	t_list			*l;

	l = e->chanel;
	while (l)
	{
		c = l->content;
		if (ft_strcmp(c->name, ch) == 0)
		{
			l = c->s;
			while (l)
			{
				if (l->valid != cs)
					ft_send(l->valid, BF(cs), (size_t)le, e);
				l = l->next;
			}
			return ;
		}
		l = l->next;
	}
}

static void			ft_irc_cmd_file_reply_parse(t_env *e, int cs, t_file *f)
{
	if (f->info.dest[0] == '#')
		ft_irc_cmd_file_reply_chanel(e, cs, f->info.dest,
								e->fds[cs].buff_len);
	else
		ft_irc_cmd_file_reply_user(e, f->info.dest,
								e->fds[cs].buffer, e->fds[cs].buff_len);
}

static void		ft_irc_cmd_file_reply_split(t_env *e, int cs, void *ptr, int l)
{
	uint64_t		*magic;
	int				new_len;

	magic = (uint64_t*)ptr;
	(void)e;
	(void)cs;
	new_len = e->fds[cs].buff_len - l;
	if (magic[0] == MH_MAGIC_FILE || magic[0] == MH_MAGIC_MTU)
	{
		printf("next is magic0\n");
		ft_memcpy(BF(cs), (void*)&magic[0], (size_t)new_len);
		ft_bzero(&BF(cs)[new_len], (size_t)l);
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
	len = (int)(SIZE_SFILE(BUF_SIZE) + f->info.l + 16);
	printf("reply_broadcast: buff_len = %d psize = %d\n",e->fds[cs].buff_len , len);
	ft_irc_cmd_file_reply_parse(e, cs, f);
	if (e->fds[cs].buff_len > len && f->info.t != f->info.p)
	{
		magic = (uint64_t*)&BF(cs)[len];
		printf("reply_split\n");
		ft_irc_cmd_file_reply_split(e, cs, (void*)magic, len);
	}
	else if ((e->fds[cs].buff_len < len && f->info.t != f->info.p) ||
			e->fds[cs].buff_len < (int)sizeof(t_fileinfo))
	{
		e->fds[cs].tfile = ft_strnew((size_t)e->fds[cs].buff_len);
		e->fds[cs].tlen = e->fds[cs].buff_len;
		ft_memcpy(e->fds[cs].tfile, BF(cs), (size_t)e->fds[cs].buff_len);
		printf("next is truckated, save data (%d)bits\n", e->fds[cs].buff_len);
	}
	return (1);
}
