/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_cmd_leave.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 19:54:05 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/12 02:44:30 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_client.h"

static int	ft_irc_cmd_leave_parse(t_env *e, char *cmd, char *vcmd)
{
	char		**tmp;
	int			i;

	tmp = ft_strsplit(cmd, ' ');
	if (tmp[0] && tmp[1] && !tmp[2])
	{
		free(tmp[0]);
		free(tmp[1]);
		if (e->chan)
			free(e->chan);
		e->chan = NULL;
		free(tmp);
		return (1);
	}
	else
	{
		i = 0;
		ft_irc_cmd_error_arg(e, vcmd, HELP_CMD_CHAN);
		while (tmp[i])
			free(tmp[i++]);
		free(tmp);
		return (0);
	}
}

int			ft_irc_cmd_leave(t_env *e, int cs)
{
	char		*tmp;

	if (BL(cs) > 6 && ft_strncmp(RB(cs), CMD_LEAVE, 6) == 0)
	{
		tmp = ft_strjoin("PART", &RB(cs)[6]);
		if (ft_irc_cmd_leave_parse(e, tmp, CMD_LEAVE))
		{
			ft_send(e->sock.s, tmp, ft_strlen(RB(cs)) - 1, e);
			ft_irc_update_prompt(e);
			ft_history_cmd_add(e, RB(cs));
		}
		free(tmp);
		return (1);
	}
	return (0);
}
