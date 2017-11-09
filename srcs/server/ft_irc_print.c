/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 20:03:35 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/09 21:23:21 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.h"

void		ft_irc_print_header(char *buff, t_env *e, char *code)
{
	ft_strcat(buff, ":");
	ft_strcat(buff, e->hostname);
	ft_strcat(buff, " ");
	ft_strcat(buff, code);
	ft_strcat(buff, " ");
}

void 		ft_irc_print_header_msg(char *buff, t_env *e, int cs)
{
	ft_strcat(buff, ":");
	ft_strcat(buff, e->fds[cs].username);
	ft_strcat(buff, "~!");
	ft_strcat(buff, e->fds[cs].user.user);
	ft_strcat(buff, "@");
	ft_strcat(buff, e->fds[cs].ipv4);
	ft_strcat(buff, " ");
}

void		ft_irc_print(char *buff, t_env *e, int cs, char *code)
{
	ft_bzero(buff, 1024);
	ft_irc_print_header(buff, e, code);
	if (e->fds[cs].username[0] != '\0')
		ft_strcat(buff, e->fds[cs].username);
	else
		ft_strcat(buff, "*");
	ft_strcat(buff, " ");
}
