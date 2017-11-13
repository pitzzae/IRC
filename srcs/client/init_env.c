/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 15:41:39 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/13 14:10:10 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_client.h"

void		init_env(t_env *e)
{
	int		i;
	struct rlimit	rlp;

	e->state = "getrlimit";
	e->history = NULL;
	X(-1, getrlimit(RLIMIT_NOFILE, &rlp), e);
	e->maxfd = rlp.rlim_cur;
	e->state = "malloc";
	e->fds = (t_fd*)Xv(NULL, malloc(sizeof(*e->fds) * e->maxfd), e);
	i = 0;
	while (i < e->maxfd)
	{
		clean_fd(&e->fds[i]);
		i++;
	}
}
