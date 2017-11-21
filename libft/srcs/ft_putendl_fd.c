/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 11:25:19 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/21 14:13:59 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_putendl_fd(char *str, int fd)
{
	write(fd, str, ft_strlen(str));
	ft_putchar_fd('\n', fd);
}
