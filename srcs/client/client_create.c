/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 14:20:06 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/22 12:20:26 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_client.h"

static void		client_create_success(t_env *e, char *ip, int port)
{
	char			*tmp;
	uint64_t		*magic;

	tmp = ft_strjoin("Connected on '", ip);
	tmp = ft_strjoin_free(tmp, ":", 1);
	tmp = ft_strjoin_free(tmp, ft_itoa(port), 3);
	tmp = ft_strjoin_free(tmp, "'\n", 1);
	ft_irc_print(e, tmp, (int)ft_strlen(tmp), 0);
	free(tmp);
	tmp = malloc((int)(16 + sizeof(t_fileinfo)));
	ft_bzero(tmp, (int)(16 + sizeof(t_fileinfo)));
	magic = (uint64_t*)&tmp[0];
	magic[0] = MH_MAGIC_INIT;
	e->connect = 1;
	ft_send(e->sock.s, tmp, (int)(16 + sizeof(t_fileinfo)), e);
	free(tmp);
}

static void		client_create_fail(t_env *e, char *ip, int port)
{
	char			*tmp;

	tmp = ft_strjoin("Fail to connect on '", ip);
	tmp = ft_strjoin_free(tmp, ":", 1);
	tmp = ft_strjoin_free(tmp, ft_itoa(port), 3);
	tmp = ft_strjoin_free(tmp, "'\n", 1);
	ft_irc_print(e, tmp, (int)ft_strlen(tmp), 0);
	free(tmp);
	if (e->host)
		free(e->host);
	e->host = NULL;
	if (e->t.prompt)
		free(e->t.prompt);
	e->t.prompt = ft_strdup("IRC$>");
	e->t.p_len = (int)ft_strlen(e->t.prompt);
	e->host = NULL;
	e->connect = 0;
}

int				client_is_connected(t_env *e)
{
	if (e->connect == 1)
		return (1);
	else
	{
		if (e->t.prompt)
		{
			free(e->t.prompt);
			e->t.prompt = ft_strdup("IRC$>");
			e->t.p_len = (int)ft_strlen(e->t.prompt);
		}
		ft_irc_print(e, NO_CONN, (int)ft_strlen(NO_CONN), 0);
		return (0);
	}
}

void			client_create(t_env *e, char *ip, int port)
{
	int				r;

	e->state = "getprotoname";
	e->sock.pe = (struct protoent*)XV(NULL, getprotobyname("tcp"), e);
	e->state = "socket";
	e->sock.s = X(-1, socket(PF_INET, SOCK_STREAM, e->sock.pe->p_proto), e);
	e->state = "gethostbyname";
	e->sock.hi = (struct hostent*)XV(NULL, gethostbyname(ip), e);
	e->sock.sin.sin_family = AF_INET;
	e->sock.sin.sin_addr.s_addr = inet_addr(e->sock.hi->h_name);
	e->sock.sin.sin_port = htons(port);
	e->state = "connect";
	r = X(-1, connect(e->sock.s, (struct sockaddr*)&e->sock.sin,
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
