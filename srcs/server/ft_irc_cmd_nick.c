/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_cmd_nick.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 19:04:53 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/09 18:12:32 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_server.h"

int	ft_irc_cmd_nick(t_env *e, int cs)
{
	int			i;

	if (e->fds[cs].buff_len > 4 && ft_strncmp(e->fds[cs].buffer, "NICK", 4) == 0)
	{
		if (e->fds[cs].buff_len > 6 && e->fds[cs].buff_len < 15)
		{
			e->fds[cs].argv = &e->fds[cs].buffer[5];
			i = ft_strfocur(&e->fds[cs].buffer[5], '\n');
			ft_bzero(e->fds[cs].username, 10);
			ft_strcpy(e->fds[cs].username, &e->fds[cs].buffer[5]);
			e->fds[cs].username[i] = '\0';
		}
		else
			ft_irc_error(e, cs, "432", NICK_ERR);
		if (ft_strlen(&e->fds[cs].username[0]) > 0 && e->fds[cs].user.host &&
				e->fds[cs].connect == 0)
			ft_irc_motd(e, cs);
		return (1);
	}
	return (0);
}
