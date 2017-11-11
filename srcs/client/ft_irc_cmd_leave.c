/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_cmd_leave.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 19:54:05 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/11 22:15:38 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_client.h"

int			ft_irc_cmd_leave(t_env *e, int cs)
{
	char		*tmp;

	if (BL(cs) > 6 && ft_strncmp(RB(cs), "/leave", 6) == 0)
	{
		tmp = ft_strjoin("PART", &RB(cs)[6]);
		ft_send(e->sock.s, tmp, ft_strlen(RB(cs)) - 1, e);
		free(tmp);
		ft_history_cmd_add(e, RB(cs));
		return (1);
	}
	return (0);
}
