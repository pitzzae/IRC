/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_terminos_move.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <null>                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 13:31:14 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/11 14:08:42 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_client.h"

void		ft_terminos_clean_line(t_env *e)
{
	int			cur;

	tputs(tgetstr("cb", NULL), 1, ft_myputchar);
	tputs(tgetstr("ce", NULL), 1, ft_myputchar);
	cur = e->t.cur;
	while (cur > 0)
	{
		tputs(tgetstr("le", NULL), 1, ft_myputchar);
		cur--;
	}
}