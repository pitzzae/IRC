/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_user_is_master_chanel.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <null>                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 16:02:06 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/12 16:11:44 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_server.h"

char		*ft_irc_user_is_master_chanel(t_list *chan, char *user)
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
			res[0] = '@';
		l = l->next;
	}
	return (res);
}
