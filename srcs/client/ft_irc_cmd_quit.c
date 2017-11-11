/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_cmd_quit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 19:54:28 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/11 21:29:40 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_client.h"

static void	client_close(t_env *e, int cs)
{
	close(cs);
	clean_fd(&e->fds[cs]);
	printf("connection #%d close\n", cs);
	ft_history_cmd_clear(e);
	ft_reset_termios(e);
	exit (1);
}

int			ft_irc_cmd_quit(t_env *e, int cs, int force)
{
	if ((BL(cs) > 5 && ft_strncmp(RB(cs), "/quit", 4) == 0) || force == 1)
	{
		if (force == 1)
			client_close(e, cs);
		else
			ft_send(e->sock.s, "QUIT\n", 5, e);
		return (1);
	}
	return (0);
}
