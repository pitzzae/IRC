/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_motd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 19:11:18 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/07 20:11:02 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.h"

int	ft_irc_motd(t_env *e, int cs)
{
	char				buff[1024];

	e->fds[cs].connect = 1;
	ft_irc_print(&buff[0], e, cs, "001");
	ft_strcat(&buff[0], WEL_MSG);
	ft_strcat(&buff[0], "\n");
	ft_send(cs, &buff[0], ft_strlen(&buff[0]), e);
	return (0);
}