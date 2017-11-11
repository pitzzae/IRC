/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 14:20:06 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/11 13:00:38 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_client.h"

void			client_create(t_env *e, char *ip, int port)
{
	e->sock.pe = (struct protoent*)Xv(NULL, getprotobyname("tcp"),
									"getprotoname");
	e->sock.s = X(-1, socket(PF_INET, SOCK_STREAM, e->sock.pe->p_proto),
									"socket");
	e->sock.hi = (struct hostent*)Xv(NULL, gethostbyname(ip),
									"gethostbyname");
	e->sock.sin.sin_family = AF_INET;
	e->sock.sin.sin_addr.s_addr = inet_addr(e->sock.hi->h_name);
	e->sock.sin.sin_port = htons(port);
	X(-1, connect(e->sock.s,(struct sockaddr*)&e->sock.sin,
				sizeof(e->sock.sin)), "connect");
	e->fds[0].type = FD_LOCAL;
	e->fds[0].fct_read = client_write;
	e->fds[0].r_buffer = ft_strnew(0);
	e->fds[e->sock.s].type = FD_CLIENT;
	e->fds[e->sock.s].fct_write = client_read;
}