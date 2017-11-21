/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_parse_privmsg.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 20:17:36 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/21 14:13:56 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_server.h"

t_privmsg			*ft_irc_parse_privmsg(t_env *e, int cs)
{
	t_privmsg		*privmsg;
	char			*msg;
	int				ocur;

	privmsg = NULL;
	msg = &e->fds[cs].buffer[7];
	ocur = ft_strocur(msg, ' ');
	if (ft_strfocur(msg, ' ') != 0)
		ft_irc_error(e, cs, "411", NO_RECIP);
	else if (ocur >= 2)
	{
		privmsg = malloc(sizeof(t_privmsg));
		privmsg->dest = &msg[1];
		privmsg->msg = &msg[ft_strnocur(msg, ' ', 2) + 1];
		privmsg->dest[ft_strfocur(privmsg->dest, ' ')] = '\0';
		privmsg->msg[ft_strfocur(privmsg->msg, '\n')] = '\0';
	}
	else
		ft_irc_error(e, cs, "412", NO_TEXT_FOUND);
	return (privmsg);
}
