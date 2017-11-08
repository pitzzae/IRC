/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_get_chanel.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 00:56:51 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/08 01:03:26 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.h"

t_chanel		*ft_irc_get_chanel(t_list *lst, char *name)
{
	t_chanel		*c;
	t_list			*l;

	l = lst;
	c = NULL;
	while (l)
	{
		c = l->content;
		if (ft_strcmp(c->name, name) == 0)
			break ;
		l = l->next;
		c = NULL;
	}
	return (c);
}