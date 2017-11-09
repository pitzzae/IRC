/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_cmd_leave_print.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 19:33:47 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/09 19:40:17 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.h"

static void	ft_irc_cmd_leave_broadcast(t_env *e, char *buff, char *cname)
{
	t_list			*l;
	t_chanel		*c;

	l = e->chanel;
	while (l)
	{
		c = l->content;
		if (ft_strcmp(c->name, cname) == 0)
		{
			l = c->s;
			while (l)
			{
				ft_send(l->valid, buff, ft_strlen(buff), e);
				l = l->next;
			}
			return ;
		}
		l = l->next;
	}
}

void		ft_irc_cmd_leave_print(t_env *e, int cs, char *name)
{
	char			buff[1024];

	ft_bzero(buff, 1024);
	ft_strcat(buff, ":");
	ft_strcat(buff, e->fds[cs].username);
	ft_strcat(buff, "!~");
	ft_strcat(buff, e->fds[cs].user.user);
	ft_strcat(buff, "@");
	ft_strcat(buff, e->fds[cs].ipv4);
	ft_strcat(buff, " PART :");
	ft_strcat(buff, name);
	ft_strcat(buff, "\n");
	ft_send(cs, buff, ft_strlen(buff), e);
	ft_irc_cmd_leave_broadcast(e, buff, name);
}
