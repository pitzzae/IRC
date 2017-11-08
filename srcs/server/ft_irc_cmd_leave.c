/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_cmd_leave.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 00:16:36 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/08 19:58:39 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.h"

static t_list	*ft_irc_remove_fd_chanle(t_list **c, int cs)
{
	t_list		*l;
	t_list		*new;
	t_list		*tmp;

	l = (*c);
	new = NULL;
	while (l)
	{
		if (l->valid != cs)
		{
			tmp = ft_lstnew(NULL, 0);
			tmp->valid = l->valid;
			ft_lstdelone(&l, u_del);
			if (new)
				ft_lstaddend_free(&new, tmp, u_del);
			else
				new = tmp;
		}
		if (l)
			l = l->next;
	}
	return (new);
}

static void		ft_irc_cmd_leave_find_chan(t_chanel **c, t_env *e, int cs)
{
	int			fd_chan;
	t_list		*l;

	l = (*c)->s;
	while (l)
	{
		fd_chan = l->valid;
		if (fd_chan == cs && ft_strcmp(e->fds[cs].chanel, (*c)->name) == 0)
		{
			(*c)->s = ft_irc_remove_fd_chanle(&(*c)->s, cs);
			return ;
		}
		if (l)
			l = l->next;
	}
}

int				ft_irc_cmd_leave(t_env *e, int cs)
{
	t_chanel	*c;
	t_list		*l;

	l = e->chanel;
	while (l)
	{
		c = l->content;
		ft_irc_cmd_leave_find_chan(&c, e, cs);
		l = l->next;
	}
	e->chanel = ft_irc_clear_empty_chanel(e->chanel);
	return (0);
}