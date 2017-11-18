/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_cmd_msgchanel.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 20:07:16 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/12 21:24:12 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_server.h"

static void	ft_irc_cmd_msgchanel_fd(t_env *e, int cs, t_chanel *c, char *msg)
{
	char		buff[1024];
	char		*tmp;
	t_list		*l;
	int			len;

	l = c->s;
	len = 11 + ft_strlen(c->name) + ft_strlen(msg);
	ft_bzero(&buff[0], 1024);
	ft_irc_print_header_msg(&buff[0], e, cs);
	len += ft_strlen(&buff[0]);
	tmp = ft_strnew(len);
	ft_strcat(tmp, &buff[0]);
	ft_strcat(tmp, "PRIVMSG ");
	ft_strcat(tmp, c->name);
	ft_strcat(tmp, " :");
	ft_strcat(tmp, msg);
	ft_strcat(tmp, "\n");
	while (l)
	{
		if (l->valid != cs)
			ft_send(l->valid, tmp, len, e);
		l = l->next;
	}
	free(tmp);
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
	free(msg);
	return (ft_irc_error(e, cs, "404", NO_CHANEL));
}
