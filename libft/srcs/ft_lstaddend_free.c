/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddend_free.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 15:36:03 by gtorresa          #+#    #+#             */
/*   Updated: 2017/10/23 19:03:23 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_lstaddend_free(t_list **alst, t_list *newlst,
		void (*del)(void *, size_t))
{
	t_list	*tmp;

	tmp = (*alst);
	if (newlst)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = ft_lstnew(newlst->content, newlst->content_size);
		tmp->next->select = newlst->select;
		ft_lstdelone(&newlst, del);
	}
}
