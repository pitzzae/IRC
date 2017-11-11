/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_cmd_msg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 19:54:12 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/11 22:06:16 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_client.h"

int			ft_irc_cmd_msg(t_env *e, int cs)
{
	char		*tmp;

	if (BL(cs) > 4 && ft_strncmp(RB(cs), "/msg", 4) == 0)
	{
		tmp = ft_strjoin("PRIVMSG", &RB(cs)[4]);
		ft_send(e->sock.s, tmp, ft_strlen(RB(cs)) + 3, e);
		free(tmp);
		ft_history_cmd_add(e, RB(cs));
		return (1);
	}
	return (0);
}
