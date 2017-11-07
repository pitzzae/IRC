/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_cmd_who.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 19:06:28 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/07 19:49:49 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.h"

int	ft_irc_cmd_who(t_env *e, int cs)
{
	if (e->fds[cs].buff_len == 3 &&
		ft_strncmp(e->fds[cs].buffer, "WHO\n", 4) == 0)
	{
		e->fds[cs].argv = &e->fds[cs].buffer[4];
		return (1);
	}
	return (0);
}