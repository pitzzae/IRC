/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_cmd_msgpriv.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 20:06:23 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/10 17:16:15 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_server.h"

static void	ft_irc_cmd_msgpriv_fd(t_env *e, int cs, t_privmsg *msg, int send)
{
	char		buff[1024];

	ft_bzero(buff, 1024);
	ft_irc_print_header_msg(&buff[0], e, send);
	ft_strcat(buff, "PRIVMSG ");
	ft_strcat(buff, msg->dest);
	ft_strcat(buff, " :");
	ft_strcat(buff, msg->msg);
	ft_strcat(buff, "\n");
	ft_send(cs, buff, ft_strlen(buff), e);
}

int			ft_irc_cmd_msgpriv(t_env *e, int cs, t_privmsg *msg)
{
	int			i;

	i = 0;
	while (i < e->maxfd)
	{
		if (ft_strcmp(e->fds[i].username, msg->dest) == 0)
		{
			ft_irc_cmd_msgpriv_fd(e, i, msg, cs);
			free(msg);
			return (0);
		}
		i++;
	}
	free(msg);
	return (ft_irc_error(e, cs, "401", NO_NICK));
}
