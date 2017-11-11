/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_write.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 15:42:10 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/11 15:30:42 by gtorresa         ###   ########.fr       */
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
			send(e->sock.s, e->fds[cs].r_buffer, ft_strlen(e->fds[cs].r_buffer), 0);
			free(e->fds[cs].r_buffer);
			e->fds[cs].r_buffer = ft_strnew(0);
			e->t.cur = ft_strlen(e->t.prompt);
			ft_client_prompt(e, 0);
		}
	}
}
