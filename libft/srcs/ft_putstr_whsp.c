/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_whsp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 13:53:22 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/21 14:13:59 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_putstr_whsp(char *str, char c, unsigned long len)
{
	int			i;
	int			j;

	i = 0;
	j = len - ft_strlen(str);
	if ((unsigned long)ft_strlen(str) < len)
	{
		while (i < j)
		{
			write(1, &c, 1);
			i++;
		}
	}
	else
		write(1, &c, 1);
	write(1, str, ft_strlen(str));
}
