/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 15:06:12 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/21 14:13:59 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_strncat(char *dst, const char *src, size_t length)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dst[j])
		j++;
	while (i < length)
	{
		dst[j + i] = src[i];
		i++;
	}
	return (dst);
}
