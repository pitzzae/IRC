/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 15:45:27 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/15 01:33:59 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_client.h"

void	check_fd(t_env *e)
{
	int	i;

	i = 0;
	while ((i < e->maxfd) && (e->r > 0))
	{
		if (FD_ISSET(i, &e->fd_read) && (e->fds[i].type == FD_CLIENT || e->fds[i].type == FD_LOCAL))
			e->fds[i].fct_read(e, i);
		if (FD_ISSET(i, &e->fd_write) && (e->fds[i].type == FD_CLIENT || e->fds[i].type == FD_LOCAL))
			e->fds[i].fct_write(e, i);
		if (FD_ISSET(i, &e->fd_read) ||
			FD_ISSET(i, &e->fd_write))
			e->r--;
		ft_irc_send_files(e, i);
		i++;
	}
}
