/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_user_is_master_chanel.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 16:02:06 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/22 16:02:08 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_server.h"

static char	ft_irc_user_is_master_chanel1(t_list *lst, int fd)
{
	t_list		*l;

	l = lst;
	while(l)
	{
		if (l->valid == fd)
			return ('@');
		l = l->next;
	}
	return ('\0');
}

char		*ft_irc_user_is_master_chanel(t_list *chan, char *user, int fd)
{
	char		*res;
	t_chanel	*c;
	t_list		*l;

	l = chan;
	res = ft_strnew(1);
	res[0] = '\0';
	while (l)
	{
		c = l->content;
		if (ft_strcmp(c->owner, user) == 0)
			res[0] = ft_irc_user_is_master_chanel1(c->s,fd);
		l = l->next;
	}
	return (res);
}
