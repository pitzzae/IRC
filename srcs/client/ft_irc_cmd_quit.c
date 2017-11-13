/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_cmd_quit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 19:54:28 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/13 14:09:57 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_client.h"

/*TODO
 * Add message support on QUIT
 * */

static void	client_close_free(t_env * e)
{
	free(e->t.prompt);
	if (e->fds[0].r_buffer)
		free(e->fds[0].r_buffer);
	if (e->host)
		free(e->host);
	if (e->nick)
		free(e->nick);
	if (e->chan)
		free(e->chan);
	if (e->fds)
		free(e->fds);
}

static void	client_close(t_env *e, int cs)
{
	ft_terminos_clean_line(e);
	if (e->host)
	{
		close(cs);
		clean_fd(&e->fds[cs]);
		printf("Close connection on %s:%d\n", e->host, e->port);
	}
	else
		ft_putendl("Close IRC client");
	ft_history_cmd_clear(e);
	ft_reset_termios(e);
	client_close_free(e);
	exit (1);
}

int			ft_irc_cmd_quit(t_env *e, int cs, int force)
{
	if ((BL(cs) > 5 && ft_strncmp(RB(cs), CMD_QUIT, 4) == 0) || force == 1)
	{
		if (force == 1 || e->sock.s >= 0)
			client_close(e, cs);
		else
			ft_send(e->sock.s, "QUIT\n", 5, e);
		return (1);
	}
	return (0);
}
