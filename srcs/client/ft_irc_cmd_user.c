/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_cmd_user.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 19:54:35 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/12 02:17:10 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_client.h"

static int	ft_irc_cmd_user_parse(t_env *e, char *cmd, char *vcmd)
{
	char		**tmp;
	int			i;

	tmp = ft_strsplit(cmd, ' ');
	if (tmp[0] && tmp[1] && tmp[2] && tmp[3] && tmp[4] && !tmp[5])
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
		ft_irc_cmd_error_arg(e, vcmd, HELP_CMD_USER);
		while (tmp[i])
			free(tmp[i++]);
		free(tmp);
		return (0);
	}
}

int			ft_irc_cmd_user(t_env *e, int cs)
{
	char		*tmp;

	if (BL(cs) > 5 && ft_strncmp(RB(cs), CMD_USER, 5) == 0)
	{
		tmp = ft_parse_irc_cmd_convert(&RB(cs)[1], 4);
		if (ft_irc_cmd_user_parse(e, tmp, CMD_USER))
		{
			ft_send(e->sock.s, tmp, ft_strlen(RB(cs)) - 1, e);
			ft_history_cmd_add(e, RB(cs));
		}
		free(tmp);
		return (1);
	}
	return (0);
}
