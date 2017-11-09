/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_get_chanel.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 00:56:51 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/08 04:27:28 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.h"

t_chanel		*ft_irc_get_chanel(t_list *lst, char *name)
{
	t_chanel		*c;
	t_list			*l;
	int				i;

	l = lst;
	c = NULL;
	i = ft_strfocur(name, '\n');
	name[i] = '\0';
	while (l)
	{
		c = l->content;
		if (ft_strcmp(c->name, name) == 0)
			return (c);
		l = l->next;
		c = NULL;
	}
	return (c);
}
