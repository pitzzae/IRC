/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 15:38:14 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/21 14:13:56 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static void		ft_putbuf(char *buf)
{
	ft_putstr(buf);
	ft_bzero(buf, 48);
}

void			ft_puthex(const char *s, const size_t len)
{
	char		buf[48];
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	ft_bzero(buf, 48);
	while (i < len)
	{
		if (((unsigned long)s[i] & 0x00F0) == 0)
			buf[j++] = '0';
		ft_putbase((unsigned long)s[i++] & 0x00FF, &buf[j++], 16);
		if (((unsigned long)s[i - 1] & 0x00F0) != 0)
			j++;
		if (i % 16 == 0)
		{
			ft_putbuf(buf);
			j = 0;
		}
		else
			buf[j++] = ' ';
	}
	if (buf[0])
		ft_putbuf(buf);
}
