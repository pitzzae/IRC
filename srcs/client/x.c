/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 15:41:04 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/18 15:43:43 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_client.h"

int		x_int(int err, int res, t_env *e)
{
	if (res == err)
	{
		fprintf(stderr, "%s error (%s)\n",
				e->state, strerror(errno));
		if (e->is_init != 1)
			exit(1);
	}
	return (res);
}

void	*x_void(void *err, void *res, t_env *e)
{
	if (res == err)
	{
		fprintf(stderr, "%s error (%s)\n",
				e->state, strerror(errno));
		if (e->is_init != 1)
			exit(1);
	}
	return (res);
}
