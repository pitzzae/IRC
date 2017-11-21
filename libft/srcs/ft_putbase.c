/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putbase.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 15:01:43 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/21 14:13:59 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static void			*ft_strcat_chr(char *dst, const char c)
{
	size_t		j;

	j = 0;
	while (dst[j] != '\0')
		j++;
	dst[j++] = c;
	dst[j] = '\0';
	return (dst);
}

void				ft_putbase(unsigned long n, char *buff, int base)
{
	char		c;

	if (n / base > 0)
	{
		ft_putbase((n / base), buff, base);
		n = n % base;
	}
	c = (char)(n < 10 ? '0' : 'a' - 10);
	c = (char)(c + n);
	ft_strcat_chr(buff, c);
}
