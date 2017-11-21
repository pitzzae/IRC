/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_parse_reply_handle.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 17:00:55 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/21 15:05:13 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_client.h"

static void	ft_irc_parse_reply_sys_replace_cursor(int len)
{
	while (len > 0)
	{
		tputs(tgetstr("le", NULL), 1, ft_myputchar);
		len--;
	}
}

static void	ft_irc_parse_nick_allready_user(t_env *e)
{
	int			len;

	len = (int)ft_strlen(e->nick);
	free(e->nick);
	e->nick = NULL;
	ft_irc_update_prompt(e);
	e->t.cur = (int)ft_strlen(e->t.prompt);
	ft_irc_parse_reply_sys_replace_cursor(len);
}

static void	ft_irc_parse_no_such_channel(t_env *e)
{
	int			len;

	len = 1;
	if (e->chan)
	{
		len += (int)ft_strlen(e->chan);
		free(e->chan);
	}
	e->chan = NULL;
	ft_irc_update_prompt(e);
	e->t.cur = (int)ft_strlen(e->t.prompt);
	ft_irc_parse_reply_sys_replace_cursor(len);
}

void		ft_irc_parse_reply_handle(t_env *e, int code, t_reply *r)
{
	if (e->nick && code == 433)
		ft_irc_parse_nick_allready_user(e);
	else if (code == 403 || code == 451)
		ft_irc_parse_no_such_channel(e);
	else if (e->nick && code == 1)
		e->file_rdy = 1;
	else if (e->nick && ft_strcmp(r->arg2, "NOTICE") == 0)
		dprintf(7, "%s %s %s %s", r->arg1, r->arg2, r->arg3, r->arg4);
}
