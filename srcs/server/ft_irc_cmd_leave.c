/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_cmd_leave.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 00:16:36 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/12 19:23:47 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_server.h"

static t_list	*ft_irc_remove_fd_chanle(t_list **c, int cs)
{
	t_list			*l;
	t_list			*new;
	t_list			*tmp;

	l = (*c);
	new = NULL;
	while (l)
	{
		if (l->valid != cs)
		{
			tmp = ft_lstnew(NULL, 0);
			tmp->valid = l->valid;
			ft_lstdelone(&l, u_del);
			if (new)
				ft_lstaddend_free(&new, tmp, u_del);
			else
				new = tmp;
		}
		if (l)
			l = l->next;
	}
	return (new);
}

static int		ft_irc_cmd_leave_find_chan(t_chanel **c, char *chan, int cs)
{
	int				fd_chan;
	t_list			*l;

	l = (*c)->s;
	while (l)
	{
		fd_chan = l->valid;
		if (fd_chan == cs && ft_strcmp(chan, (*c)->name) == 0)
		{
			(*c)->s = ft_irc_remove_fd_chanle(&(*c)->s, cs);
			return (1);
		}
		if (l)
			l = l->next;
	}
	return (0);
}

void			ft_irc_leave(t_env *e, int cs, char *chan)
{
	t_chanel		*c;
	t_list			*l;
	int				loop;

	l = e->chanel;
	if (ft_strfocur(chan, '\n') > 0)
		chan[ft_strfocur(chan, '\n')] = '\0';
	while (l)
	{
		c = l->content;
		loop = ft_irc_cmd_leave_find_chan(&c, chan, cs);
		while (loop)
			loop = ft_irc_cmd_leave_find_chan(&c, chan, cs);
		l = l->next;
	}
	e->chanel = ft_irc_clear_empty_chanel(e->chanel);
	e->fds[cs].chan_user = ft_irc_chan_user_del(e->fds[cs].chan_user, chan);
	ft_irc_cmd_leave_print(e, cs, chan);
	if (e->fds[cs].chanel)
		free(e->fds[cs].chanel);
	e->fds[cs].chanel = NULL;
}

int				ft_irc_cmd_leave(t_env *e, int cs)
{
	char			*cmd;

	if (e->fds[cs].buff_len > 4 &&
		ft_strncmp(e->fds[cs].buffer, "PART", 4) == 0)
	{
		if (ft_strlen(e->fds[cs].buffer) >= 7 && e->fds[cs].connect == 1)
		{
			cmd = &e->fds[cs].buffer[5];
			if (cmd[0] == '#')
			{
				ft_irc_leave(e, cs, cmd);
				return (1);
			}
			else
				return (ft_irc_error(e, cs, "403", NOT_CHAN));
		}
		else if (e->fds[cs].connect == 0)
			return (ft_irc_error(e, cs, "451", NOT_REGIS));
		else
			return (ft_irc_error(e, cs, "461", STX_ERR));
	}
	return (0);
}
