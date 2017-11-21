/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_clear_empty_chanel.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 19:54:18 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/21 14:13:56 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_server.h"

static t_list	*ft_irc_clean_empty_chanel(t_list *lst)
{
	t_list		*l;
	t_list		*tmp;

	l = lst;
	tmp = NULL;
	while (l)
	{
		if (((t_chanel*)(l->content))->s)
		{
			if (tmp == NULL)
				tmp = ft_lstnew(l->content, l->content_size);
			else
				ft_lstaddend_free(&tmp, ft_lstnew(l->content, l->content_size),
					u_del);
		}
		l = l->next;
	}
	ft_lstdel(&lst, u_del);
	return (tmp);
}

t_list			*ft_irc_clear_empty_chanel(t_list *lst)
{
	t_list		*l;
	t_chanel	*c;

	l = lst;
	while (l)
	{
		c = l->content;
		if (!c->s)
			return (ft_irc_clean_empty_chanel(lst));
		l = l->next;
	}
	return (lst);
}
