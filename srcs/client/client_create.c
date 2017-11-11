/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 14:20:06 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/11 23:58:16 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_client.h"

static void		client_create_success(t_env *e, char *ip, int port)
{
	char			*tmp;

	tmp = ft_strjoin("Connected on '", ip);
	tmp = ft_strjoin_free(tmp, ":", 1);
	tmp = ft_strjoin_free(tmp, ft_itoa(port), 3);
	tmp = ft_strjoin_free(tmp, "'\n", 1);
	ft_irc_print(e, tmp, ft_strlen(tmp), 0);
	free(tmp);
	e->connect = 1;
}

static void		client_create_fail(t_env *e, char *ip, int port)
{
	char			*tmp;

	tmp = ft_strjoin("Fail to connect on '", ip);
	tmp = ft_strjoin_free(tmp, ":", 1);
	tmp = ft_strjoin_free(tmp, ft_itoa(port), 3);
	tmp = ft_strjoin_free(tmp, "'\n", 1);
	ft_irc_print(e, tmp, ft_strlen(tmp), 0);
	free(tmp);
	e->connect = 0;
}

int				client_is_connected(t_env *e)
{
	if (e->connect == 1)
		return (1);
	else
	{
		ft_irc_print(e, NO_CONN, ft_strlen(NO_CONN), 0);
		return (0);
	}
}

void			client_create(t_env *e, char *ip, int port)
{
	int				r;

	e->state = "getprotoname";
	e->sock.pe = (struct protoent*)Xv(NULL, getprotobyname("tcp"), e);
	e->state = "socket";
	e->sock.s = X(-1, socket(PF_INET, SOCK_STREAM, e->sock.pe->p_proto), e);
	e->state = "gethostbyname";
	e->sock.hi = (struct hostent*)Xv(NULL, gethostbyname(ip), e);
	e->sock.sin.sin_family = AF_INET;
	e->sock.sin.sin_addr.s_addr = inet_addr(e->sock.hi->h_name);
	e->sock.sin.sin_port = htons(port);
	e->state = "connect";
	r = X(-1, connect(e->sock.s,(struct sockaddr*)&e->sock.sin,
				sizeof(e->sock.sin)), e);
	if (r != -1)
	{
		e->state = NULL;
		e->fds[e->sock.s].type = FD_CLIENT;
		e->fds[e->sock.s].fct_read = client_read;
		client_create_success(e, ip, port);
	}
	else
		client_create_fail(e, ip, port);
}
