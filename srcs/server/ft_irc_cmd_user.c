/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_cmd_user.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 19:03:22 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/09 18:12:21 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.h"

static void		ft_irc_cmd_user_set(t_env *e, int cs)
{
	char			**tmp;

	tmp = ft_strsplit(&e->fds[cs].buffer[5], ' ');
	e->fds[cs].user.user = tmp[0];
	e->fds[cs].user.host = tmp[1];
	e->fds[cs].user.srv_name = tmp[2];
	e->fds[cs].user.real_user = tmp[3];
	free(tmp);
}

int				ft_irc_cmd_user(t_env *e, int cs)
{
	int				i;

	if (e->fds[cs].buff_len > 6 &&
		ft_strncmp(e->fds[cs].buffer, "USER ", 5) == 0)
	{
		e->fds[cs].argv = &e->fds[cs].buffer[5];
		i = ft_strfocur(&e->fds[cs].buffer[5], '\n');
		e->fds[cs].buffer[i + 5] = '\0';
		if (e->fds[cs].connect == 0 &&
				ft_strocur(&e->fds[cs].buffer[5], ' ') == 3)
			ft_irc_cmd_user_set(e, cs);
		else if (e->fds[cs].connect == 1)
			ft_irc_error(e, cs, "462", ALLRD_REGIS);
		else
			ft_irc_error(e, cs, "461", STX_ERR);
		if (ft_strlen(&e->fds[cs].username[0]) > 0 && e->fds[cs].user.host &&
				e->fds[cs].connect == 0)
			ft_irc_motd(e, cs);
		return (1);
	}
	return (0);
}
