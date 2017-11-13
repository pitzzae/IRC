/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_cmd_join.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 00:04:44 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/13 16:46:35 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_server.h"

static void	ft_irc_cmd_join_chanel_add(t_chanel **c, int cs)
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

static void	ft_irc_cmd_join_chanel_search(t_env *e, int cs, char *name)
{
	t_chanel	*c;
	t_list		*l;

	c = ft_irc_get_chanel(e->chanel, name);
	if (!c)
	{
		c = ft_irc_create_chanel(e, cs, name);
		if (!e->chanel)
			e->chanel = ft_lstnew(c, sizeof(t_chanel));
		else
			ft_lstaddend_free(&e->chanel,
				ft_lstnew(c, sizeof(t_chanel)), u_del);
	}
	ft_irc_cmd_join_chanel_add(&c, cs);
	if (e->fds[cs].chanel)
		free(e->fds[cs].chanel);
	e->fds[cs].chanel = ft_strdup(c->name);
	if ((l = ft_irc_chan_user_add(e->fds[cs].chan_user, c->name)) != NULL)
	{
		e->fds[cs].chan_user = l;
		ft_irc_cmd_join_print(e, cs, name);
	}
}

static int	ft_irc_cmd_join_chanel_valid(t_env *e, int cs, char *cmd)
{
	size_t			i;

	i = 10;
	if (ft_strlen(cmd) > i)
		ft_irc_error(e, cs, "403", NOT_CHAN);
	else
		ft_irc_cmd_join_chanel_search(e, cs, cmd);
	return (1);
}

int			ft_irc_cmd_join(t_env *e, int cs)
{
	char		*cmd;

	if (e->fds[cs].buff_len > 4 &&
		ft_strncmp(e->fds[cs].buffer, "JOIN", 4) == 0)
	{
		if (ft_strlen(e->fds[cs].buffer) >= 7 && e->fds[cs].connect == 1)
		{
			cmd = &e->fds[cs].buffer[5];
			if (ft_strcmp(cmd , "0\n") == 0)
				ft_irc_leave_all_chan(e, cs);
			else if (cmd[0] == '#')
			{
				ft_irc_cmd_join_chanel_valid(e, cs, cmd);
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
