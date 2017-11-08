/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 15:36:03 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/08 17:25:36 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_lstaddend(t_list **alst, t_list *newlst)
{
	t_list	*tmp;

	tmp = (*alst);
	if (newlst)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = ft_lstnew(newlst->content, newlst->content_size);
		tmp->next->select = newlst->select;
		tmp->next->valid = newlst->valid;
		tmp->next->prev = tmp;
	}
}
