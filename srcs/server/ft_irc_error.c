/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 19:12:56 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/12 20:01:00 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_server.h"

int	ft_irc_error(t_env *e, int cs, char *code, char *msg)
{
	char				buff[1024];

	ft_irc_print(&buff[0], e, cs, code);
	if (e->fds[cs].argv)
		ft_strncat(&buff[0], e->fds[cs].argv, ft_strlen(e->fds[cs].argv) - 1);
	else
		ft_strcat(&buff[0], STX_ERR);
	ft_strcat(&buff[0], msg);
	ft_strcat(&buff[0], "\n");
	ft_send(cs, &buff[0], ft_strlen(&buff[0]), e);
	return (1);
}
