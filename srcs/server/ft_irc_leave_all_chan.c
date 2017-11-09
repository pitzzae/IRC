/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_leave_all_chan.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 12:43:48 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/09 14:34:15 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.h"

int			ft_irc_leave_all_chan(t_env *e, int cs)
{
	t_list		*l;

	l = e->fds[cs].chan_user;
	while (l)
	{
		ft_irc_leave(e, cs, (char*)(l->content));
		l = e->fds[cs].chan_user;
	}
	return (0);
}