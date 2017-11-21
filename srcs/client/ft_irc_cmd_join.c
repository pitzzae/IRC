/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_cmd_join.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 19:53:58 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/21 14:13:56 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_client.h"

static char	*ft_irc_cmd_chan_set(char *chan)
{
	int			i;

	i = ft_strfocur(chan, '\n');
	if (i >= 0)
		chan[i] = '\0';
	return (chan);
}

static void	ft_irc_cmd_join_chan_update(t_env *e, char **tmp)
{
	free(tmp[0]);
	if (e->chan)
		free(e->chan);
	e->chan = ft_irc_cmd_chan_set(tmp[1]);
	if (ft_strcmp(e->chan, "0") == 0)
	{
		free(tmp[1]);
		e->chan = NULL;
	}
	free(tmp);
}

static int	ft_irc_cmd_join_parse(t_env *e, char *cmd, char *vcmd)
{
	char		**tmp;
	int			i;

	tmp = ft_strsplit(cmd, ' ');
	if (tmp[0] && tmp[1] && !tmp[2])
	{
		ft_irc_cmd_join_chan_update(e, tmp);
		return (1);
	}
	else
	{
		i = 0;
		ft_irc_cmd_error_arg(e, vcmd, HELP_CMD_CHAN);
		while (tmp[i])
			free(tmp[i++]);
		free(tmp);
		return (0);
	}
}

int			ft_irc_cmd_join(t_env *e, int cs)
{
	char		*tmp;

	if (BL(cs) > 5 && RB(cs)[5] == ' ' && ft_strncmp(RB(cs), CMD_JOIN, 5) == 0)
	{
		tmp = ft_parse_irc_cmd_convert(&RB(cs)[1], 4);
		if (ft_irc_cmd_join_parse(e, tmp, CMD_JOIN))
		{
			ft_send(e->sock.s, tmp, ft_strlen(RB(cs)) - 1, e);
			ft_irc_update_prompt(e);
			ft_history_cmd_add(e, RB(cs));
		}
		free(tmp);
		return (1);
	}
	return (0);
}
