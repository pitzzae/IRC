/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 15:46:25 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/10 15:46:25 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_client.h"

void	main_loop(t_env *e)
{
	e->timeout.tv_sec = 1;
	e->timeout.tv_usec = 0;
	while (1)
	{
		init_fd(e);
		do_select(e);
		check_fd(e);
	}
}
