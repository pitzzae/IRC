/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_read_is_magic.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 15:50:57 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/22 12:25:16 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_server.h"

static int	client_read_magic_file(t_env *e, int cs, int len)
{
	uint64_t	*magic;
	void		*tmp;

	magic = ((uint64_t *)&e->fds[cs].buf_read[0]);
	if (magic[0] == MH_MAGIC_FILE || magic[0] == MH_MAGIC_REPLY)
	{
		tmp = malloc((size_t)len);
		ft_memcpy(tmp, e->fds[cs].buf_read, (size_t)len);
		free(e->fds[cs].buffer);
		e->fds[cs].buffer = tmp;
		e->fds[cs].buff_len = len;
		FD_COPY(&e->fd_read, &e->fd_write);
		FT_FD_ZERO(&e->fds[cs].buf_read);
		e->fds[cs].cmd = 1;
		return (1);
	}
	else if (magic[0] == MH_MAGIC_INIT)
	{
		FT_FD_ZERO(&e->fds[cs].buf_read);
		e->fds[cs].f_support = 1;
		return (1);
	}
	return (0);
}

static int	client_read_magic_mtu_check(t_env *e, int cs, int len)
{
	uint64_t	*magic_end;
	void		*tmp;

	magic_end = ((uint64_t *)&e->fds[cs].buf_read[len - 8]);
	if (magic_end[0] != MH_MAGIC_MTU)
		e->fds[cs].mtu_test = 1;
	tmp = malloc((size_t)len);
	ft_memcpy(tmp, e->fds[cs].buf_read, (size_t)len);
	if (len == BUF_SIZE)
	{
		free(e->fds[cs].buffer);
		e->fds[cs].buffer = tmp;
		e->fds[cs].buff_len = len;
		FD_COPY(&e->fd_read, &e->fd_write);
		e->fds[cs].cmd = 1;
	}
	else
	{
		e->fds[cs].cmd_mtu = tmp;
		e->fds[cs].cmd_mtu_len = len;
	}
	FT_FD_ZERO(&e->fds[cs].buf_read);
	return (1);
}

static int	client_read_magic_mtu_stop(t_env *e, int cs, int len)
{
	uint64_t	*magic_end;

	magic_end = ((uint64_t *)&e->fds[cs].buf_read[len - 8]);
	if (magic_end[0] == MH_MAGIC_MTU)
	{
		e->fds[cs].mtu_test = 0;
		free(e->fds[cs].buffer);
		e->fds[cs].buffer = e->fds[cs].cmd_mtu;
		e->fds[cs].buff_len = e->fds[cs].cmd_mtu_len;
		FD_COPY(&e->fd_read, &e->fd_write);
		e->fds[cs].cmd = 1;
	}
	FT_FD_ZERO(&e->fds[cs].buf_read);
	return (1);
}

static int	client_read_magic_mtu(t_env *e, int cs, int len)
{
	uint64_t	*magic;

	magic = ((uint64_t *)&e->fds[cs].buf_read[0]);
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
