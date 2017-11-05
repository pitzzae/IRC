/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_loic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/05 18:27:22 by gtorresa          #+#    #+#             */
/*   Updated: 2017/10/23 19:03:23 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void		ft_str_replace_chr(char *str, int c, int d)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			str[i] = (char)d;
		i++;
	}
}
