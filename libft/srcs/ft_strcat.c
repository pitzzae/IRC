/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 15:06:12 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/21 14:13:57 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_strcat(char *dst, const char *src)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dst[j] != '\0')
		j++;
	while (src[i] != '\0')
	{
		dst[j + i] = src[i];
		i++;
	}
	dst[j + i] = '\0';
	return (dst);
}
