/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 14:57:55 by gtorresa          #+#    #+#             */
/*   Updated: 2017/10/23 19:03:22 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	while ((*alst)->next)
		ft_lstdel(&(*alst)->next, (*del));
	ft_lstdelone(alst, (*del));
}
