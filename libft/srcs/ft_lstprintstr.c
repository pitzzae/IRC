/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprintstr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 14:43:45 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/21 14:13:59 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_lstprintstr(const t_list *lst)
{
	size_t	i;

	i = 0;
	while (lst != NULL)
	{
		ft_putstr("[ ");
		ft_putnbr(i);
		ft_putstr(" ] ");
		ft_putendl((char *)lst->content);
		lst = lst->next;
		i++;
	}
}
