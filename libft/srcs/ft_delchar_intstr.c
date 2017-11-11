/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delchar_intstr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 15:49:33 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/11 17:26:51 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char		*ft_delchar_intstr(char *s, int p)
{
	int			i;
	int			len;

	i = p;
	len = ft_strlen(s);
	while (i < len)
	{
		s[i] = s[i + 1];
		i++;
	}
	s[i] = '\0';
	return (s);
}
