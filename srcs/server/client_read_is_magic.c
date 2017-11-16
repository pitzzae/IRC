/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_read_is_magic.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 15:50:57 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/16 16:00:54 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_server.h"

static int	client_read_magic_file(t_env *e, int cs, int len)
{
	uint64_t	*magic;
	void		*tmp;

	magic = ((uint64_t *) &e->fds[cs].buf_read[0]);
	if (magic[0] == MH_MAGIC_FILE)
	{
		tmp = malloc((size_t)len);
		ft_memcpy(tmp, e->fds[cs].buf_read, (size_t)len);
		free(e->fds[cs].buffer);
		e->fds[cs].buffer = tmp;
		e->fds[cs].buff_len = len;
		FD_COPY(&e->fd_read, &e->fd_write);
		printf("magic command\n");
		FT_FD_ZERO(&e->fds[cs].buf_read);
		return (1);
	}
	return (0);
}

static int	client_read_magic_mtu_check(t_env *e, int cs, int len)
{
	uint64_t	*magic_end;
	void		*tmp;

	magic_end = ((uint64_t *) &e->fds[cs].buf_read[len - 8]);
	if (magic_end[0] != MH_MAGIC_MTU)
		e->fds[cs].mtu_test = 1;
	tmp = malloc((size_t)len);
	ft_memcpy(tmp, e->fds[cs].buf_read, (size_t)len);
	free(e->fds[cs].buffer);
	e->fds[cs].buffer = tmp;
	e->fds[cs].buff_len = len;
	FD_COPY(&e->fd_read, &e->fd_write);
	printf("magic_mtu command\n");
	FT_FD_ZERO(&e->fds[cs].buf_read);
	return (1);
}

static int	client_read_magic_mtu_stop(t_env *e, int cs, int len)
{
	uint64_t	*magic_end;

	magic_end = ((uint64_t *) &e->fds[cs].buf_read[len - 8]);
	if (magic_end[0] == MH_MAGIC_MTU)
		e->fds[cs].mtu_test = 0;
	FT_FD_ZERO(&e->fds[cs].buf_read);
	printf("magic_mtu command find mtu stop -> %d\n", e->fds[cs].mtu_test);
	return (1);
}

static int	client_read_magic_mtu(t_env *e, int cs, int len)
{
	uint64_t	*magic;

	magic = ((uint64_t *) &e->fds[cs].buf_read[0]);
	if (magic[0] == MH_MAGIC_MTU)
		return (client_read_magic_mtu_check(e, cs, len));
	else if (e->fds[cs].mtu_test == 1)
		return (client_read_magic_mtu_stop(e, cs, len));
	return (0);
}

int			client_read_is_magic(t_env *e, int cs, int len)
{
	if (len > (int)(8 + sizeof(t_fileinfo)))
	{
		if (client_read_magic_file(e, cs, len))
			return (1);
		else if (client_read_magic_mtu(e, cs, len))
			return (1);
	}
	return (0);
}