/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_send.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 23:31:07 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/21 14:13:56 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_server.h"

size_t			ft_send(int cs, void *buff, size_t len, t_env *e)
{
	size_t		r;
	t_fd		*f;

	r = 0;
	f = &e->fds[cs];
	if (f->type == FD_CLIENT)
	{
		r = send(cs, buff, len, 0);
		f->b_recive += len;
	}
	return (r);
}
