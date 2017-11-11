/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_opt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 15:41:50 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/11 22:52:54 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_client.h"

void	get_opt(t_env *e, int ac, char **av)
{
	char		**tmp;

	if (ac == 3)
	{
		e->port = atoi(av[2]);
		e->host = av[1];
	}
	else if (ac == 2)
	{
		tmp = ft_strsplit(av[1], ' ');
		if (tmp[0] && tmp[1] && !tmp[2])
		{
			e->port = atoi(tmp[1]);
			e->host = tmp[0];
		}
		free(tmp);
	}
}
