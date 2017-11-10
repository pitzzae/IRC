/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 14:20:06 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/10 16:41:11 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_client.h"

void			client_create(t_env *e, char *ip, int port)
{
	e->sock.s = X(-1, socket(AF_INET, SOCK_STREAM, 0), "socket");
	e->sock.hi = (struct hostent*)Xv(NULL, gethostbyname(ip),
									 "gethostbyname");
	e->sock.sin.sin_addr = *(struct in_addr*)e->sock.hi->h_addr;
	e->sock.sin.sin_port = htons(port);
	e->sock.sin.sin_family = AF_INET;
	X(-1, connect(e->sock.s,(struct sockaddr*)&e->sock.sin,
				  sizeof(e->sock.sin)), "connect");
	e->fds[0].type = FD_LOCAL;
	e->fds[0].fct_read = client_write;
	e->fds[e->sock.s].type = FD_CLIENT;
	e->fds[e->sock.s].fct_read = client_read;
}