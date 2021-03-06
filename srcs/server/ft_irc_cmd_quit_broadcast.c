/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_cmd_quit_broadcast.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 18:03:48 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/13 19:55:53 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_server.h"

void		ft_irc_cmd_quit_broadcast_print(t_env *e, int cs, char *m, char *n)
{
	char			buff[1024];

	ft_bzero(buff, 1024);
	ft_strcat(buff, ":");
	ft_strcat(buff, n);
	ft_strcat(buff, "!~");
	ft_strcat(buff, e->fds[cs].user.user);
	ft_strcat(buff, "@");
	ft_strcat(buff, e->fds[cs].ipv4);
	ft_strcat(buff, " QUIT :");
	ft_strcat(buff, m);
	ft_strcat(buff, "\n");
	ft_send(cs, buff, ft_strlen(buff), e);
}

static int	ft_irc_cmd_quit_broadcast_find_fd(t_list *lfd, int cs)
{
	t_list		*l;

	l = lfd;
	while (l)
	{
		if (l->valid == cs)
			return (1);
		l = l->next;
	}
	return (0);
}

static void	ft_irc_cmd_quit_broadcast_chanel(t_env *e, t_list *lfd,
												int cs, char *msg)
{
	t_list		*l;

	l = lfd;
	while (l)
	{
		if (l->valid != cs)
		{
			ft_irc_cmd_quit_broadcast_print(e, l->valid, msg,
											e->fds[cs].username);
		}
		l = l->next;
	}
}

void		ft_irc_cmd_quit_broadcast(t_env *e, int cs, char *cmd)
{
	t_chanel	*c;
	t_list		*l;
	char		*tmp;

	l = e->chanel;
	tmp = "\"Leaving...\"";
	if (ft_strlen(cmd) > 1)
	{
		if (cmd[0] != '\n' || cmd[0] != ' ')
			tmp = &cmd[1];
	}
	while (l)
	{
		c = l->content;
		if (ft_irc_cmd_quit_broadcast_find_fd(c->s, cs))
			ft_irc_cmd_quit_broadcast_chanel(e, c->s, cs, tmp);
		l = l->next;
	}
}
