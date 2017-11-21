/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_opt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 15:41:50 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/21 14:13:56 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_client.h"

static void	ft_irc_print_usage(char **av)
{
	fprintf(stderr, USAGE, av[0]);
	exit(1);
}

void		get_opt(t_env *e, int ac, char **av)
{
	char		**tmp;

	if (ac == 3)
	{
		e->port = ft_atoi(av[2]);
		e->host = ft_strdup(av[1]);
	}
	else if (ac == 2)
	{
		tmp = ft_strsplit(av[1], ' ');
		if (tmp[0] && tmp[1] && !tmp[2])
		{
			e->port = ft_atoi(tmp[1]);
			free(tmp[1]);
			e->host = tmp[0];
			free(tmp);
		}
		else
		{
			free(tmp);
			ft_irc_print_usage(av);
		}
	}
	else if (ac != 1)
		ft_irc_print_usage(av);
}
