/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_send.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 23:31:07 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/21 14:23:04 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_server.h"

size_t			ft_send(int cs, void *buff, size_t len, t_env *e)
{
	size_t			r;
	t_fd			*f;

	r = 0;
	e->fds[cs].err_size = sizeof(unsigned int);
	f = &e->fds[cs];
	if (f->type == FD_CLIENT)
	{
		getsockopt(cs, SOL_SOCKET, SO_ERROR,
				&e->fds[cs].err_code, &e->fds[cs].err_size);
		if (e->fds[cs].err_code == 0)
			r = send(cs, buff, len, 0);
		else
			ft_irc_cmd_quit(e, cs, 1);
		f->b_recive += len;
	}
	return (r);
}
