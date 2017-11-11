/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addchar_intstr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 14:30:19 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/11 14:55:42 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_addchar_intstr(char *s, char c, int p)
{
	char		*tmp;
	int			len;
	int			i;
	int			j;

	len = ft_strlen(s) + 1;
	tmp = ft_strnew(len);
	i = 0;
	j = 0;
	while (i < len)
	{
		if (i == p)
		{
			tmp[i] = c;
			j++;
		}
		tmp[i + j] = s[i];
		i++;
	}
	free(s);
	i = 0;
	while (i < len)
	{
		ft_putchar_fd(tmp[i], 2);
		i++;
	}
	ft_putendl_fd("", 2);
	return (tmp);
}