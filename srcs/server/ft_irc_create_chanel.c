/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_create_chanel.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 01:08:07 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/09 18:56:22 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_server.h"

t_chanel		*ft_irc_create_chanel(t_env *e, int cs, char *name)
{
	t_chanel		*c;
	int				i;

	c = malloc(sizeof(t_chanel));
	c->name = ft_strdup(name);
	i = ft_strfocur(c->name, '\n');
	if (i > 0)
		c->name[i - 1] = '\0';
	c->owner = ft_strdup(e->fds[cs].user.real_user);
	c->s = ft_lstnew(NULL, 0);
	c->s->valid = cs;
	return (c);
}
