/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 00:02:40 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/06 14:25:42 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.h"

void	main_loop(t_env *e)
{
	e->timeout.tv_sec = 10;
	e->timeout.tv_usec = 0;
	while (1)
	{
		init_fd(e);
		do_select(e);
		check_fd(e);
	}
}
