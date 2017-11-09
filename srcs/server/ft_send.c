/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_send.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 23:31:07 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/07 23:36:35 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.h"

size_t			ft_send(int cs, void *buff, size_t len, t_env *e)
{
	size_t		r;

	r = 0;
	if (e->fds[cs].type == FD_CLIENT)
	{
		r = send(cs, buff, len, 0);
		e->fds[cs].b_recive += len;
	}
	return (r);
}
