/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_create_chanel.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 01:08:07 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/08 01:15:40 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.h"

t_chanel		*ft_irc_create_chanel(t_env *e, int cs, char *name)
{
	t_chanel		*c;

	c = malloc(sizeof(t_chanel));
	c->name = ft_strdup(name);
	c->owner = e->fds[cs].user.real_user;
	c->s = ft_lstnew(&cs, sizeof(int));
	return (c);
}