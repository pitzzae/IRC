/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_cmd_msg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 11:58:12 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/14 11:58:30 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_server.h"

int		ft_irc_cmd_msg(t_env *e, int cs)
{
	t_privmsg	*msg;

	if ((e->fds[cs].buff_len >= 7 && e->fds[cs].connect &&
		 ft_strncmp(e->fds[cs].buffer, "PRIVMSG", 7) == 0))
	{
		msg = ft_irc_parse_privmsg(e, cs);
		if (msg)
		{
			if (msg->dest[0] == '#')
				ft_irc_cmd_msgchanel(e, cs, msg);
			else
				ft_irc_cmd_msgpriv(e, cs, msg);
			return (1);
		}
	}
	else if (ft_strncmp(e->fds[cs].buffer, "PRIVMSG", 7) == 0)
		ft_irc_error(e, cs, "451", NOT_REGIS);
	return (0);
}
