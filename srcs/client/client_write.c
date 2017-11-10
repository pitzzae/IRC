/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_write.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 15:42:10 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/10 20:55:03 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_client.h"

void	client_write(t_env *e, int cs)
{
	char		*tmp;
	char		buff[7];
	char		c;

	(void)cs;
	tmp = ft_strnew(0);
	while (read(0, &c, 6) != 0)
	{
		ft_bzero(buff, 7);
		ft_strncat(buff, &c, 1);
		tmp = ft_strjoin_free(tmp, &buff[0], 1);
		if (c == '\n')
			break ;
	}
	send(e->sock.s, tmp, ft_strlen(tmp), 0);
}
