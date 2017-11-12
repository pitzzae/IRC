/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_opt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 00:04:34 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/09 18:57:38 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_server.h"

void	get_opt(t_env *e, int ac, char **av)
{
	if (ac != 2)
	{
		fprintf(stderr, USAGE, av[0]);
		exit(1);
	}
	e->port = ft_atoi(av[1]);
}
