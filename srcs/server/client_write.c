/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_write.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 00:04:12 by gtorresa          #+#     #+#             *//*   Updated: 2017/11/07 22:16:17 by gtorresa         ###   ########.fr       */

/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.h"

void	client_write(t_env *e, int cs)
{
	int	i;
	int	type;

	type = ft_parse_irc_cmd(e, cs);
	if (type)
	{
		i = 0;
		while (i < e->maxfd)
		{
			if ((e->fds[i].type == FD_CLIENT) && (i != cs))
			{
				ft_send(i, e->fds[cs].buffer, e->fds[cs].buff_len, e);
			}
			i++;
		}
	}
	free(e->fds[cs].buffer);
	e->fds[cs].buffer = ft_strnew(0);
	e->fds[cs].buff_len = 0;
	e->fds[cs].argv = NULL;
}
