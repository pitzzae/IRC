/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_parse_reply.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 13:23:10 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/12 16:51:00 by gtorresa         ###   ########.fr       */
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

static char	*ft_irc_parse_reply_sys(t_reply *r)
{
	char		*str;

	str = ft_strjoin("Reply(", r->arg2);
	str = ft_strjoin_free(str, "): ", 1);
	str = ft_strjoin_free(str, r->arg3, 1);
	str = ft_strjoin_free(str, " ", 1);
	str = ft_strjoin_free(str, r->arg4, 1);
	str = ft_strjoin_free(str, "\n", 1);
	return (str);
}

static char	*ft_irc_parse_reply_msg(t_reply *r)
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
		str = ft_irc_parse_reply_sys(r);
	return (str);
}

char		*ft_irc_parse_reply(t_reply *r)
{
	if (!r->arg4 && r->arg1 && r->arg2 && r->arg3)
		return (ft_irc_parse_reply_chan(r));
	else if (r->arg1 && r->arg2 && r->arg3 && r->arg4)
		return (ft_irc_parse_reply_msg(r));
	else
		return (NULL);
}
