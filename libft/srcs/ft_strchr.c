/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 15:06:12 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/21 14:13:57 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strchr(const char *src, int c)
{
	(void)c;
	(void)src;
	while (*src != (char)c && *src != '\0')
		src++;
	if (*src == (char)c)
		return ((char *)src);
	return (NULL);
}
