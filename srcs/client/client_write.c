/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_write.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 15:42:10 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/11 14:53:23 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_client.h"

void	client_write(t_env *e, int cs)
{
	if (cs == 0)
	{
		ft_terms_read(e, cs);
		if (ft_strocur(e->fds[cs].r_buffer, '\n') > 0)
		{
			dprintf(2, "%s\n", e->fds[0].r_buffer);
			send(e->sock.s, e->fds[cs].r_buffer, ft_strlen(e->fds[cs].r_buffer), 0);
			free(e->fds[cs].r_buffer);
			e->fds[cs].r_buffer = ft_strnew(0);
		}
		else
		{
			ft_putendl_fd(" -> no \\n", 7);
		}
	}
}
