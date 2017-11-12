/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_parse_reply.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <null>                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 13:23:10 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/12 14:17:31 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_client.h"

static char	*ft_irc_parse_reply_sys(t_reply *r)
{
	char		*str;

	str = ft_strjoin(r->arg1, " ");
	str = ft_strjoin_free(str, r->arg2, 1);
	str = ft_strjoin_free(str, " ", 1);
	str = ft_strjoin_free(str, r->arg3, 1);
	str = ft_strjoin_free(str, "\n", 1);
	return (str);
}

static char	*ft_irc_parse_reply_msg(t_reply *r)
{
	char		*str;

	str = ft_strjoin(r->arg1, " ");
	str = ft_strjoin_free(str, r->arg2, 1);
	str = ft_strjoin_free(str, " ", 1);
	str = ft_strjoin_free(str, r->arg3, 1);
	str = ft_strjoin_free(str, " ", 1);
	str = ft_strjoin_free(str, r->arg4, 1);
	str = ft_strjoin_free(str, "\n", 1);
	return (str);
}

char		*ft_irc_parse_reply(t_reply *r)
{
	if (!r->arg4 && r->arg1 && r->arg2 && r->arg3)
		return (ft_irc_parse_reply_sys(r));
	else if (r->arg1 && r->arg2 && r->arg3 && r->arg4)
		return (ft_irc_parse_reply_msg(r));
	else
		return (NULL);
}