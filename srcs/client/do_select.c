/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 15:42:00 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/15 01:44:39 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_client.h"

void	do_select(t_env *e)
{
	e->r = select(e->max + 1, &e->fd_read, &e->fd_write, NULL, NULL);
	dprintf(7, "do_select %d\n", e->r);
}
