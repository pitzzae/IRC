/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_cmd_msgchanel.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 20:07:16 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/09 21:47:23 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_irc_server.h"

static void	ft_irc_cmd_msgchanel_fd(t_env *e, int cs, t_chanel *c, char *msg)
{
	char		buff[1024];
	t_list		*l;

	l = c->s;
	ft_bzero(buff, 1024);
	ft_irc_print_header_msg(&buff[0], e, cs);
	ft_strcat(buff, "PRIVMSG ");
	ft_strcat(buff, c->name);
	ft_strcat(buff, " :");
	ft_strcat(buff, msg);
	ft_strcat(buff, "\n");
	while (l)
	{
		if (l->valid != cs)
			ft_send(l->valid, buff, ft_strlen(buff), e);
		l = l->next;
	}
}

int			ft_irc_cmd_msgchanel(t_env *e, int cs, t_privmsg *msg)
{
	t_list		*l;
	t_chanel	*c;

	l = e->chanel;
	while (l)
	{
		c = l->content;
		if (ft_strcmp(c->name, msg->dest) == 0)
		{
			ft_irc_cmd_msgchanel_fd(e, cs, c, msg->msg);
			free(msg);
			return (1);
		}
		l = l->next;
	}
	ft_irc_error(e, cs, "404", NO_CHANEL);
	free(msg);
	return (0);
}