/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_cmd_msg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 19:54:12 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/13 16:48:20 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_client.h"

static int	ft_irc_cmd_msg_parse(t_env *e, char *cmd, char *vcmd)
{
	char		**tmp;
	int			i;

	tmp = ft_strsplit(cmd, ' ');
	if (tmp[0] && tmp[1] && tmp[2])
	{
		i = 0;
		while (tmp[i])
			free(tmp[i++]);
		free(tmp);
		return (1);
	}
	else
	{
		i = 0;
		ft_irc_cmd_error_arg(e, vcmd, HELP_CMD_MSG);
		while (tmp[i])
			free(tmp[i++]);
		free(tmp);
		return (0);
	}
}

int			ft_irc_cmd_msg(t_env *e, int cs)
{
	char		*tmp;

	if (BL(cs) > 4 && RB(cs)[4] == ' ' && ft_strncmp(RB(cs), CMD_MSG, 4) == 0)
	{
		tmp = ft_strjoin("PRIVMSG", &RB(cs)[4]);
		if (ft_irc_cmd_msg_parse(e, tmp, CMD_MSG))
		{
			ft_send(e->sock.s, tmp, ft_strlen(RB(cs)) + 3, e);
			ft_history_cmd_add(e, RB(cs));
		}
		free(tmp);
		return (1);
	}
	return (0);
}
