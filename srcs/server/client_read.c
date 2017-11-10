/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_read.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 00:03:25 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/10 13:57:55 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_server.h"

static void	ft_packet_agreg(t_env *e, int cs, int len)
{
	char		*tmp;

	tmp = malloc(e->fds[cs].buff_len + len + 1);
	ft_bzero(tmp, e->fds[cs].buff_len + len + 1);
	ft_memcpy(tmp, e->fds[cs].buffer, e->fds[cs].buff_len);
	ft_memcpy(&tmp[e->fds[cs].buff_len], e->fds[cs].buf_read, len);
	free(e->fds[cs].buffer);
	e->fds[cs].buffer = tmp;
	e->fds[cs].buff_len = e->fds[cs].buff_len + len;
	if (ft_strocur(e->fds[cs].buffer, '\n') > 0)
		FD_COPY(&e->fd_read, &e->fd_write);
	if (e->fds[cs].buff_len > MAX_CMD_SIZE)
	{
		free(e->fds[cs].buffer);
		e->fds[cs].buffer = ft_strnew(0);
		e->fds[cs].buff_len = 0;
	}
	FD_ZERO(&e->fds[cs].buf_read);
}

void		client_read(t_env *e, int cs)
{
	int			r;
	int			i;

	r = recv(cs, e->fds[cs].buf_read, BUF_SIZE, 0);
	e->fds[cs].recive = r;
	if (r <= 0)
	{
		ft_irc_cmd_quit(e, cs, 1);
	}
	else
	{
		i = 0;
		while (i < e->maxfd)
		{
			if ((e->fds[i].type == FD_CLIENT) && (i == cs))
			{
				e->fds[cs].b_send += r;
				ft_packet_agreg(e, cs, r);
			}
			i++;
		}
	}
}
