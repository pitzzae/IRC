/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_cmd_nick.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 19:04:53 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/21 14:13:56 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_server.h"

static int	ft_irc_cmd_nick_allready_use(t_env *e, char *nick)
{
	char		*tmp_nick;
	int			i;

	tmp_nick = ft_strdup(nick);
	i = ft_strfocur(nick, '\n');
	if (i >= 0)
		tmp_nick[i] = '\0';
	i = 0;
	while (i < e->maxfd)
	{
		if (ft_strcmp(e->fds[i].username, tmp_nick) == 0)
		{
			free(tmp_nick);
			return (1);
		}
		i++;
	}
	free(tmp_nick);
	return (0);
}

static int	ft_irc_cmd_nick_is_valid(char *buff, int buff_len)
{
	if (buff_len > 5 && buff[4] == ' ' && buff_len < 15)
	{
		if (ft_strocur(&buff[5], ' ') == 0)
			return (1);
	}
	return (0);
}

static void	ft_irc_cmd_nick_set(t_env *e, int cs)
{
	int			i;

	e->fds[cs].argv = &e->fds[cs].buffer[5];
	i = ft_strfocur(&e->fds[cs].buffer[5], '\n');
	ft_bzero(e->fds[cs].username, 10);
	ft_strcpy(e->fds[cs].username, &e->fds[cs].buffer[5]);
	e->fds[cs].username[i] = '\0';
}

int			ft_irc_cmd_nick(t_env *e, int cs)
{
	if (e->fds[cs].buff_len > 4 &&
			ft_strncmp(e->fds[cs].buffer, "NICK", 4) == 0)
	{
		if (ft_irc_cmd_nick_is_valid(e->fds[cs].buffer, e->fds[cs].buff_len))
		{
			if (ft_irc_cmd_nick_allready_use(e, &e->fds[cs].buffer[5]) == 0)
				ft_irc_cmd_nick_set(e, cs);
			else
				ft_irc_error(e, cs, "433", NICK_USE);
		}
		else
			ft_irc_error(e, cs, "432", NICK_ERR);
		if (ft_strlen(&e->fds[cs].username[0]) > 0 && e->fds[cs].user.user &&
				e->fds[cs].connect == 0)
			ft_irc_motd(e, cs);
		return (1);
	}
	return (0);
}
