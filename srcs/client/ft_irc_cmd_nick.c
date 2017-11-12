/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_cmd_nick.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 19:54:20 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/12 02:41:30 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_client.h"

static char	*ft_irc_cmd_nick_set(char *nick)
{
	int			i;

	i = ft_strfocur(nick, '\n');
	if (i >= 0)
		nick[i] = '\0';
	return (nick);
}

static int	ft_irc_cmd_nick_parse(t_env *e, char *cmd, char *vcmd)
{
	char		**tmp;
	int			i;

	tmp = ft_strsplit(cmd, ' ');
	if (tmp[0] && tmp[1] && !tmp[2])
	{
		free(tmp[0]);
		if (e->nick)
			free(e->nick);
		e->nick = ft_irc_cmd_nick_set(tmp[1]);
		ft_irc_update_prompt(e);
		free(tmp);
		return (1);
	}
	else
	{
		i = 0;
		ft_irc_cmd_error_arg(e, vcmd, HELP_CMD_NICK);
		while (tmp[i])
			free(tmp[i++]);
		free(tmp);
		return (0);
	}
}

int			ft_irc_cmd_nick(t_env *e, int cs)
{
	char		*tmp;

	if (BL(cs) > 5 && ft_strncmp(RB(cs), CMD_NICK, 5) == 0)
	{
		tmp = ft_parse_irc_cmd_convert(&RB(cs)[1], 4);
		if (ft_irc_cmd_nick_parse(e, tmp, CMD_NICK))
		{
			ft_send(e->sock.s, tmp, ft_strlen(RB(cs)) - 1, e);
			ft_history_cmd_add(e, RB(cs));
		}
		free(tmp);
		return (1);
	}
	return (0);
}
