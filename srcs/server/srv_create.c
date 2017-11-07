/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srv_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 00:03:11 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/07 12:33:45 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
# include <sys/un.h>

#include "ft_irc.h"

void			srv_create(t_env *e, int port)
{
	int				yes;

	yes = 1;
	e->sock.pe = (struct protoent*)Xv(NULL, getprotobyname("tcp"), "getprotoname");
	e->sock.s = X(-1, socket(PF_INET, SOCK_STREAM, e->sock.pe->p_proto), "socket");
	e->sock.sin.sin_family = AF_INET;
	e->sock.sin.sin_addr.s_addr = INADDR_ANY;
	e->sock.sin.sin_port = htons(port);
	X(-1, setsockopt(e->sock.s, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)), "setsockopt");
	X(-1, bind(e->sock.s, (struct sockaddr*)&e->sock.sin, sizeof(e->sock.sin)), "bind");
	X(-1, listen(e->sock.s, 42), "listen");
	e->fds[e->sock.s].type = FD_SERV;
	e->fds[e->sock.s].fct_read = srv_accept;
	e->fds[e->sock.s].fct_write = NULL;
}
