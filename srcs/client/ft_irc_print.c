/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 20:46:50 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/11 21:14:05 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_client.h"

void			ft_irc_print(t_env *e, char *msg, int len, int prompt)
{
	ft_terminos_clean_line(e);
	write(1, msg, len);
	if (prompt == 1)
	{
		ft_client_prompt(e, e->t.cur);
		e->t.cur -= ft_strlen(e->t.prompt);
	}
}