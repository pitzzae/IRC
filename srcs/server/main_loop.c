/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 00:02:40 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/15 17:57:54 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_server.h"

void sig_handler(int signo, void *ptr)
{
	static t_env		*saved = NULL;
	int					i;

	if (saved == NULL)
		saved = (t_env*)ptr;
	if (signo == SIGTERM)
	{
		printf("received SIGTERM\n");
		i = 0;
		while (i < saved->maxfd)
		{
			close(i);
			i++;
		}
		close(saved->sock.s);
		exit(0);
	}
}

void	main_loop(t_env *e)
{
	e->timeout.tv_sec = 1000;
	e->timeout.tv_usec = 0;
	if (signal(SIGTERM, (void (*)(int))sig_handler) == SIG_ERR)
		printf("\ncan't catch SIGTERM\n");
	sig_handler(890, e);
	while (1)
	{
		init_fd(e);
		do_select(e);
		check_fd(e);
	}
}
