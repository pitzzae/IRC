/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 20:03:35 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/07 20:07:35 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.h"

void		ft_irc_print(char *buff, t_env *e, int cs, int code)
{
	char				*tmp;

	ft_bzero(buff, 1024);
	ft_strcat(buff, ":");
	ft_strcat(buff, e->hostname);
	ft_strcat(buff, " ");
	tmp = ft_itoa((long)code);
	ft_strcat(buff, tmp);
	ft_strcat(buff, " ");
	if (e->fds[cs].username[0] != '\0')
		ft_strcat(buff, e->fds[cs].username);
	else
		ft_strcat(buff, "*");
	ft_strcat(buff, " ");
	free(tmp);
}