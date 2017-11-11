/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_read.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 15:42:22 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/11 15:37:50 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_client.h"

void	client_read(t_env *e, int cs)
{
	int	r;
	int	i;

	r = recv(cs, e->fds[cs].buf_read, BUF_SIZE, 0);
	if (r <= 0)
	{
		close(cs);
		clean_fd(&e->fds[cs]);
		printf("server #%d gone away\n", cs);
		ft_reset_termios(e);
		exit (1);
	}
	else
	{
		i = 0;
		while (i < e->maxfd)
		{
			if (e->fds[i].type == FD_CLIENT)
			{
				ft_terminos_clean_line(e);
				write(1, e->fds[cs].buf_read, r);
				ft_client_prompt(e, e->t.cur);
				e->t.cur -= ft_strlen(e->t.prompt);
				FD_SET(1, &e->fd_write);
			}
			i++;
		}
	}
}
