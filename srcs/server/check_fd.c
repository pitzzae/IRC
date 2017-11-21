/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 00:01:45 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/21 14:13:56 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_server.h"

void	check_fd(t_env *e)
{
	int	i;

	i = 0;
	while ((i < e->maxfd) && (e->r > 0))
	{
		e->fds[i].recive = 0;
		if (FD_ISSET(i, &e->fd_read))
			e->fds[i].fct_read(e, i);
		if (FD_ISSET(i, &e->fd_write) && e->fds[i].fct_write)
			e->fds[i].fct_write(e, i);
		if (e->fds[i].buff_len > 0 && e->fds[i].fct_write &&
				e->fds[i].cmd == 0)
			e->fds[i].fct_buffer(e, i);
		if (FD_ISSET(i, &e->fd_read) ||
			FD_ISSET(i, &e->fd_write))
			e->r--;
		i++;
	}
}
