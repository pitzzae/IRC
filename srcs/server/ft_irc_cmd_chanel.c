/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_cmd_chanel.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <null>                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 03:08:33 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/08 03:48:22 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.h"

static void	ft_irc_debug_put_chanel(t_chanel *c)
{
	t_list		*l;
	char		*tmp;

	l = c->s;
	ft_putstr("name: '");
	ft_putstr(c->name);
	ft_putstr("' owner: '");
	ft_putstr(c->owner);
	ft_putstr("' fds:[");
	while (l->next)
	{
		tmp = ft_itoa(l->valid);
		ft_putstr(tmp);
		free(tmp);
		l = l->next;
		if (l->next)
			ft_putstr(", ");
	}
	ft_putendl("]");
}

static void	ft_irc_debug_show_chanel(t_list *lst)
{
	t_chanel	*c;
	t_list		*l;

	l = lst;
	if (!l)
		ft_putendl("No chanel found");
	while (l)
	{
		c = l->content;
		ft_irc_debug_put_chanel(c);
		l = l->next;
	}
}

int		ft_irc_cmd_chanel(t_env *e, int cs)
{
	t_fd			f;

	f = e->fds[cs];
	if (e->fds[cs].buff_len == 7 &&
		ft_strncmp(e->fds[cs].buffer, "CHANEL", 6) == 0)
	{
		ft_irc_debug_show_chanel(e->chanel);
		return (1);
	}
	return (0);
}