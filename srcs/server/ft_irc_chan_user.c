/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_chan_user.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 11:45:41 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/21 14:13:56 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_server.h"

t_list			*ft_irc_chan_user_del(t_list *l, char *cname)
{
	t_list			*c;
	t_list			*new;
	t_list			*tmp;

	c = l;
	new = NULL;
	while (c)
	{
		if (ft_strcmp(cname, (char*)c->content) != 0)
		{
			tmp = ft_lstnew((char*)c->content,
					ft_strlen((char*)c->content) + 1);
			if (new)
				ft_lstaddend_free(&new, tmp, u_del);
			else
				new = tmp;
		}
		c = c->next;
	}
	if (l)
		ft_lstdel(&l, u_del);
	return (new);
}

t_list			*ft_irc_chan_user_add(t_list *l, char *cname)
{
	t_list			*c;
	char			*tmp_name;

	tmp_name = ft_strdup(cname);
	if (!l)
	{
		l = ft_lstnew(tmp_name, ft_strlen(tmp_name) + 1);
		free(tmp_name);
		return (l);
	}
	c = l;
	while (c)
	{
		if (ft_strcmp(tmp_name, (char*)c->content) == 0)
		{
			free(tmp_name);
			return (NULL);
		}
		c = c->next;
	}
	ft_lstaddend_free(&l, ft_lstnew(tmp_name, ft_strlen(tmp_name) + 1), u_del);
	free(tmp_name);
	return (l);
}
