/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_buffer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 13:17:52 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/21 14:13:56 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_server.h"

void			client_buffer(t_env *e, int cs)
{
	if (e->fds[cs].recive > 0)
		client_write(e, cs);
}
