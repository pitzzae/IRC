/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_leave_all_chan.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 12:43:48 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/09 14:29:21 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.h"

int			ft_irc_leave_all_chan(t_env *e, int cs)
{
	t_list		*l;

	l = e->fds[cs].chan_user;
	while (l)
	{
		printf("%zu\n", l->content_size);
		printf("%s\n", (char*)(l->content));
		//ft_irc_leave(e, cs, (char*)(l->content));
		l = l->next;
	}
	return (0);
}