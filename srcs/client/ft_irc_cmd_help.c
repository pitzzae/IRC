/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_cmd_help.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 21:19:54 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/21 14:13:56 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_client.h"

int			ft_irc_cmd_help(t_env *e, int cs)
{
	char			*tmp;

	if (BL(cs) > 5 && RB(cs)[5] == '\n' && ft_strncmp(RB(cs), CMD_HELP, 5) == 0)
	{
		tmp = "• /connect <machine> [port]\n"
				"• /nick <nickname>\n"
				"• /user <user> <mode> <unused> <realname>\n"
				"• /join <#chan>\n"
				"• /leave <#chan>\n"
				"• /who\n"
				"• /msg <nick>|<#chan> <message>\n"
				"• /quit\n";
		ft_irc_print(e, tmp, ft_strlen(tmp), 0);
		ft_history_cmd_add(e, RB(cs));
		return (1);
	}
	return (0);
}
