/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_write.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 00:01:45 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/21 14:13:56 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_server.h"

static void	client_buffered_command(t_env *e, int cs)
{
	if (e->fds[cs].buffer && ft_strocur(e->fds[cs].buffer, '\n') <= 1)
	{
		free(e->fds[cs].buffer);
		e->fds[cs].buffer = ft_strnew(0);
		e->fds[cs].buff_len = 0;
	}
}

void		client_write(t_env *e, int cs)
{
	int	type;

	type = ft_parse_irc_cmd(e, cs);
	if (type)
		ft_irc_error(e, cs, "421", UNK_COMMAND);
	client_buffered_command(e, cs);
	e->fds[cs].argv = NULL;
}
