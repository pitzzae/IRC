/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_read.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 15:42:22 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/21 14:13:56 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_client.h"

void	client_read(t_env *e, int cs)
{
	int	r;
	int	i;

	r = recv(cs, e->fds[cs].buf_read, BUF_SIZE, 0);
	if (r <= 0)
		ft_irc_cmd_quit(e, cs, 1);
	else
	{
		i = 0;
		while (i < e->maxfd)
		{
			if (e->fds[i].type == FD_CLIENT)
			{
				e->fds[cs].r = r;
				dprintf(7, "Read from #%d, len %d\n", cs, r);
				ft_irc_parse_return(e, cs, r);
				FD_SET(1, &e->fd_write);
			}
			i++;
		}
	}
}
