/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_client_prompt.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 13:58:39 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/21 14:13:56 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_client.h"

void			ft_client_prompt(t_env *e, int curs)
{
	int				len;

	ft_putstr(e->t.prompt);
	ft_putstr(e->fds[0].r_buffer);
	e->t.cur = ft_strlen(e->t.prompt) + curs;
	len = ft_strlen(e->t.prompt) + ft_strlen(e->fds[0].r_buffer);
	if (e->t.cur != len)
	{
		while (len > e->t.cur)
		{
			tputs(tgetstr("le", NULL), 1, ft_myputchar);
			len--;
		}
	}
}
