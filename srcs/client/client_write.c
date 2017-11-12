/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_write.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 15:42:10 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/11 19:45:44 by gtorresa         ###   ########.fr       */
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
			ft_parse_irc_cmd(e, cs);
			free(e->fds[cs].r_buffer);
			RB(cs) = ft_strnew(0);
			e->t.cur = ft_strlen(e->t.prompt);
			ft_client_prompt(e, 0);
		}
	}
}
