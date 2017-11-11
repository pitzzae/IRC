/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 17:02:13 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/11 17:05:26 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_client.h"

static void		ft_history_cmd_up(t_env *e, int fd)
{
	(void)e;
	(void)fd;
}

static void		ft_history_cmd_down(t_env *e, int fd)
{
	(void)e;
	(void)fd;
}

void			ft_history_cmd(t_env *e, int fd, char c)
{
	if (c == ARROW_UP)
		ft_history_cmd_up(e, fd);
	else if (c == ARROW_DOWN)
		ft_history_cmd_down(e, fd);
}
