/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_cmd_who.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 19:54:46 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/12 02:06:38 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_client.h"

int			ft_irc_cmd_who(t_env *e, int cs)
{
	char		*tmp;

	if (BL(cs) > 4 && ft_strncmp(RB(cs), CMD_WHO, 4) == 0)
	{
		if (ft_strlen(RB(cs)) == 5)
		{
			tmp = ft_parse_irc_cmd_convert(&RB(cs)[1], 3);
			ft_send(e->sock.s, tmp, ft_strlen(RB(cs)) - 1, e);
			free(tmp);
			ft_history_cmd_add(e, RB(cs));
		}
		else
			ft_irc_cmd_error_arg(e, CMD_WHO, HELP_CMD_WHO);
		return (1);
	}
	return (0);
}
