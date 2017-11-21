/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 00:06:17 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/21 14:13:56 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_server.h"

int		x_int(int err, int res, char *str)
{
	if (res == err)
	{
		fprintf(stderr, "%s error (%s)\n",
				str, strerror(errno));
		exit(1);
	}
	return (res);
}

void	*x_void(void *err, void *res, char *str)
{
	if (res == err)
	{
		fprintf(stderr, "%s error (%s)\n",
				str, strerror(errno));
		exit(1);
	}
	return (res);
}
