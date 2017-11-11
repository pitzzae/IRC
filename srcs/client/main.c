/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 15:42:46 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/11 22:40:49 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_client.h"

int	main(int ac, char **av)
{
	t_env	e;

	ft_bzero(&e, sizeof(e));
	init_env(&e);
	get_opt(&e, ac, av);
	if (!ft_init_termios(&e, 1))
		return (-1);
	tputs(tgetstr("cl", NULL), 1, ft_myputchar);
	if (e.host)
		client_create(&e, e.host, e.port);
	ft_irc_cmd_connect(&e, 0, 1);
	main_loop(&e);
	ft_reset_termios(&e);
	return (0);
}
