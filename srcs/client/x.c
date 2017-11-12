/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 15:41:04 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/10 15:41:09 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_client.h"

int		x_int(int err, int res, t_env *e, char *file, int line)
{
	if (res == err)
	{
		fprintf(stderr, "%s error (%s, %d): %s\n",
				e->state, file, line, strerror(errno));
		if (e->is_init != 1)
			exit (1);
	}
	return (res);
}

void	*x_void(void *err, void *res, t_env *e, char *file, int line)
{
	if (res == err)
	{
		fprintf(stderr, "%s error (%s, %d): %s\n",
				e->state, file, line, strerror(errno));
		if (e->is_init != 1)
			exit (1);
	}
	return (res);
}
