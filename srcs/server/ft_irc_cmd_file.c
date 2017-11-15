/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_cmd_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 22:28:11 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/14 22:48:36 by gtorresa         ###   ########.fr       */
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

static int		ft_irc_cmd_file_reply_broadcast(t_env *e, int cs, t_file *f)
{
	ft_bzero(f->info.source, CH_LEN + 1);
	ft_strcat(f->info.source, e->fds[cs].username);
	if (f->info.dest[0] == '#')
		ft_irc_cmd_file_reply_chanel(e, cs, f->info.dest, e->fds[cs].buff_len);
	else
		ft_irc_cmd_file_reply_user(e, f->info.dest,
			e->fds[cs].buffer, e->fds[cs].buff_len);
	return (1);
}

static int		ft_irc_cmd_file_reply_init(t_env *e, int cs, t_file *f)
{
	ft_bzero(f->info.source, CH_LEN + 1);
	ft_strcat(f->info.source, e->fds[cs].username);
	ft_send(cs, e->fds[cs].buffer, (size_t)e->fds[cs].buff_len, e);
	return (1);
}

int				ft_irc_cmd_file(t_env *e, int cs)
{
	uint64_t		*magic;
	t_fileinfo		*i;
	t_file			*f;

	if (e->fds[cs].buff_len > (int)(8 + sizeof(t_fileinfo)))
	{
		magic = ((uint64_t*)&e->fds[cs].buffer[0]);
		if (magic[0] == MH_MAGIC_FILE)
		{
			f = (t_file*)&e->fds[cs].buffer[8];
			i = &f->info;
			if (i->l >= 0 && i->l <= (int)MSG_FILE)
			{
				if (i->p == 0 && i->t == 0 && i->l == 0)
					return (ft_irc_cmd_file_reply_init(e, cs, f));
				else if (i->t > 0 && i->p <= i->t)
					return (ft_irc_cmd_file_reply_broadcast(e, cs, f));
			}
		}
	}
	return (0);
}
