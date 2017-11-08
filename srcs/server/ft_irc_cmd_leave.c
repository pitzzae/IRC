/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_cmd_leave.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 00:16:36 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/08 02:49:10 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.h"

static void	ft_free_chan_fd(void *ptr, size_t len)
{
	free(ptr);
	(void)len;
}


static void	ft_irc_leave_chan(t_chanel *c, int cs)
{
	t_list		*l;
	t_list		*prev;
	t_list		*next;

	l = c->s;
	prev = NULL;
	while (l)
	{
		next = l->next;
		if ((int)l->content == cs)
		{
			ft_lstdelone(&l, ft_free_chan_fd);
			if (prev == NULL)
				c->s = next;
			else
				prev->next = next;
		}
		prev = l;
		l = l->next;
	}
}

int		ft_irc_cmd_leave(t_env *e, int cs, char *name)
{
	t_chanel	*c;
	t_list		*l;

	l = e->chanel;
	while (l)
	{
		c = l->content;
		if (ft_strcmp(c->name, name) == 0)
		{
			ft_irc_leave_chan(c, cs);
		}
		l = l->next;
	}
	return (0);
}