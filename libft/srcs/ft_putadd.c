/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 15:11:42 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/21 14:13:56 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static void		ft_putbaseadd(unsigned long n, int base, char *buf)
{
	char		c;
	char		d[2];

	if (n / base > 0)
	{
		ft_putbaseadd((n / base), base, buf);
		n = n % base;
	}
	c = n < 10 ? '0' : 'a' - 10;
	d[0] = c + n;
	d[1] = '\0';
	ft_strcat(buf, d);
}

void			ft_putadd(void const *p, char *buf)
{
	ft_strcat(buf, "0x");
	ft_putbaseadd((unsigned long)p, 16, buf);
}
