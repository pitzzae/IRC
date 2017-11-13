/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_parse_reply.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 13:23:10 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/13 16:22:29 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_client.h"

static char	*ft_irc_parse_reply_chan(t_reply *r)
{
	char		*str;
	char		*tmp;
	int 		i;

	tmp = &r->arg1[1];
	i = ft_strfocur(tmp, '!');
	if (i >= 0)
		tmp[i] = '\0';
	if (ft_strncmp(r->arg2, "JOIN", 3) == 0)
		str = ft_strjoin(tmp, " has joined ");
	else if (ft_strncmp(r->arg2, "PART", 3) == 0)
		str = ft_strjoin(tmp, " has leave ");
	else
		return (NULL);
	str = ft_strjoin_free(str, &r->arg3[1], 1);
	str = ft_strjoin_free(str, "\n", 1);
	return (str);
}

static void	ft_irc_parse_reply_sys_replace_cursor(int len)
{
	while (len > 0)
	{
		tputs(tgetstr("le", NULL), 1, ft_myputchar);
		len--;
	}
}

static char	*ft_irc_parse_reply_sys(t_env *e, t_reply *r)
{
	char		*str;
	int			len;

	if (e->nick && ft_atoi(r->arg2) == 433)
	{
		len = ft_strlen(e->nick);
		free(e->nick);
		e->nick = NULL;
		ft_irc_update_prompt(e);
		e->t.cur = ft_strlen(e->t.prompt);
		ft_irc_parse_reply_sys_replace_cursor(len);
	}
	str = ft_strjoin("Reply(", r->arg2);
	str = ft_strjoin_free(str, "): ", 1);
	str = ft_strjoin_free(str, r->arg3, 1);
	str = ft_strjoin_free(str, " ", 1);
	str = ft_strjoin_free(str, r->arg4, 1);
	str = ft_strjoin_free(str, "\n", 1);
	return (str);
}

static char	*ft_irc_parse_reply_msg(t_env *e, t_reply *r)
{
	char		*str;
	char		*tmp;
	int			i;

	if (ft_strcmp(r->arg2, "PRIVMSG") == 0
			|| ft_strcmp(r->arg2, "PART") == 0
			|| ft_strcmp(r->arg2, "JOIN") == 0)
	{
		tmp = &r->arg1[1];
		i = ft_strfocur(tmp, '~');
		if (i >= 0)
			tmp[i] = '\0';
		str = ft_strjoin(tmp, " -> ");
		str = ft_strjoin_free(str, r->arg3, 1);
		str = ft_strjoin_free(str, " ", 1);
		str = ft_strjoin_free(str, r->arg4, 1);
		str = ft_strjoin_free(str, "\n", 1);
	}
	else
		str = ft_irc_parse_reply_sys(e, r);
	return (str);
}

char		*ft_irc_parse_reply(t_env *e, t_reply *r)
{
	if (!r->arg4 && r->arg1 && r->arg2 && r->arg3)
		return (ft_irc_parse_reply_chan(r));
	else if (r->arg1 && r->arg2 && r->arg3 && r->arg4)
		return (ft_irc_parse_reply_msg(e, r));
	else
		return (NULL);
}
