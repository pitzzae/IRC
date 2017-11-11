/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_cmd_nick.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 19:54:20 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/12 00:00:40 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_client.h"

int			ft_irc_cmd_nick(t_env *e, int cs)
{
	char			*tmp;

	if (BL(cs) > 5 && ft_strncmp(RB(cs), "/nick", 5) == 0)
	{
		tmp = ft_parse_irc_cmd_convert(&RB(cs)[1], 4);
		ft_send(e->sock.s, tmp, ft_strlen(RB(cs)) - 1, e);
		free(tmp);
		ft_history_cmd_add(e, RB(cs));
		return (1);
	}
	return (0);
}
