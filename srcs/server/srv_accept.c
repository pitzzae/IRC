/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srv_accept.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 00:00:25 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/10 13:15:45 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_server.h"

static void		ft_init_client(t_env *e, int cs)
{
	ft_bzero(e->fds[cs].username, 10);
	ft_bzero(&e->fds[cs].user, sizeof(e->fds[cs].user));
	e->fds[cs].connect = 0;
	e->fds[cs].argv = NULL;
	e->fds[cs].b_send = 0;
	e->fds[cs].b_recive = 0;
	e->fds[cs].chanel = NULL;
	e->fds[cs].chan_user = NULL;
}

void			srv_accept(t_env *e, int s)
{
	int					cs;
	struct sockaddr_in	csin;
	socklen_t			csin_len;

	csin_len = sizeof(csin);
	cs = X(-1, accept(s, (struct sockaddr*)&csin, &csin_len), "accept");
	printf("New client #%d from %s:%d\n", cs,
	inet_ntoa(csin.sin_addr), ntohs(csin.sin_port));
	clean_fd(&e->fds[cs]);
	e->fds[cs].ipv4 = inet_ntoa(csin.sin_addr);
	e->fds[cs].type = FD_CLIENT;
	e->fds[cs].fct_read = client_read;
	e->fds[cs].fct_write = client_write;
	e->fds[cs].fct_buffer = client_buffer;
	e->fds[cs].buffer = ft_strnew(0);
	e->fds[cs].buff_len = 0;
	ft_init_client(e, cs);
}
