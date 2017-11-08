/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_cmd_join.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 00:04:44 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/08 17:15:25 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.h"

static void	ft_irc_join_chanel(t_chanel **c, int cs)
{
	t_list		*l;
	t_list		*tmp;

	l = (*c)->s;
	if (!l)
	{
		(*c)->s = ft_lstnew(NULL, 0);
		(*c)->s->valid = cs;
		return ;
	}
	while (l)
	{
		if (l->valid == cs)
			return ;
		l = l->next;
	}
	tmp = ft_lstnew(NULL, 0);
	tmp->valid = cs;
	ft_lstaddend_free(&(*c)->s, tmp, u_del);
}

static void	ft_irc_join(t_env *e, int cs, char *name)
{
	t_chanel		*c;

	c = ft_irc_get_chanel(e->chanel, name);
	if (!c)
	{
		c = ft_irc_create_chanel(e, cs, name);
		if (!e->chanel)
			e->chanel = ft_lstnew(c, sizeof(t_chanel));
		else
			ft_lstaddend(&e->chanel, ft_lstnew(c, sizeof(t_chanel)));
	}
	ft_irc_join_chanel(&c, cs);
	if (e->fds[cs].chanel)
		free(e->fds[cs].chanel);
	e->fds[cs].chanel = ft_strdup(c->name);
	ft_irc_debug_show_chanel(e->chanel);
}

int	ft_irc_cmd_join(t_env *e, int cs)
{
	char		*cmd;
	t_fd		f;

	f = e->fds[cs];
	if (e->fds[cs].buff_len > 4 &&
		ft_strncmp(e->fds[cs].buffer, "JOIN", 4) == 0)
	{
		if (ft_strlen(e->fds[cs].buffer) >= 7 && e->fds[cs].connect == 1)
		{
			cmd = &e->fds[cs].buffer[5];
			if (ft_strcmp(cmd , "0\n") == 0)
				ft_irc_cmd_leave(e, cs);
			else if (cmd[0] == '#')
			{
				ft_irc_join(e, cs, cmd);
				return (1);
			}
			else
				ft_irc_error(e, cs, 403, NOT_CHAN);
		}
		else if (e->fds[cs].connect == 0)
			ft_irc_error(e, cs, 451, NOT_REGIS);
		else
			ft_irc_error(e, cs, 461, STX_ERR);
	}
	return (0);
}