/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_cmd_msg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 19:54:12 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/21 14:13:56 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_client.h"

static int	ft_irc_cmd_msg_parse(t_env *e, char *cmd, char *vcmd)
{
	char		**tmp;
	int			i;

	tmp = ft_strsplit(cmd, ' ');
	if (tmp[0] && tmp[1] && tmp[2])
	{
		i = 0;
		while (tmp[i])
			free(tmp[i++]);
		free(tmp);
		return (1);
	}
	else
	{
		i = 0;
		ft_irc_cmd_error_arg(e, vcmd, HELP_CMD_MSG);
		while (tmp[i])
			free(tmp[i++]);
		free(tmp);
		return (0);
	}
}

static void	ft_irc_cmd_msg_shortcut(t_env *e, int cs)
{
	char		*tmp;
	char		*tmp2;

	tmp = ft_strjoin(" ", e->chan);
	tmp = ft_strjoin_free(tmp, " ", 1);
	tmp = ft_strjoin_free(tmp, RB(cs), 1);
	tmp2 = ft_strjoin("PRIVMSG", tmp);
	ft_send(e->sock.s, tmp2, ft_strlen(tmp2), e);
	free(tmp2);
	tmp2 = ft_strjoin("/msg", tmp);
	ft_history_cmd_add(e, tmp2);
	free(tmp2);
	free(tmp);
}

static void	ft_irc_cmd_msg_display(t_env *e, char *msg, int p)
{
	char		*tmp;
	char		*str;

	tmp = NULL;
	if (p == 1 && msg[1])
		tmp = &msg[1];
	else if (p == 0)
		tmp = msg;
	if (tmp && e->nick && e->chan)
	{
		str = ft_strjoin(e->nick, " <- ");
		str = ft_strjoin_free(str, e->chan, 1);
		str = ft_strjoin_free(str, " :", 1);
		str = ft_strjoin_free(str, tmp, 1);
		if (p == 1)
			str = ft_strjoin_free(str, "\n", 1);
		tputs(tgetstr("up", NULL), 1, ft_myputchar);
		ft_irc_print(e, str, (int)ft_strlen(str), 0);
		free(str);
	}
}

int			ft_irc_cmd_msg(t_env *e, int cs)
{
	char		*tmp;

	if (BL(cs) > 4 && RB(cs)[4] == ' ' && ft_strncmp(RB(cs), CMD_MSG, 4) == 0)
	{
		tmp = ft_strjoin("PRIVMSG", &RB(cs)[4]);
		if (ft_irc_cmd_msg_parse(e, tmp, CMD_MSG))
		{
			ft_send(e->sock.s, tmp, ft_strlen(RB(cs)) + 3, e);
			ft_history_cmd_add(e, RB(cs));
		}
		ft_irc_cmd_msg_display(e, &RB(cs)[4], 1);
		free(tmp);
		return (1);
	}
	else if (BL(cs) > 1 && e->chan && RB(cs)[0] != '/')
	{
		ft_irc_cmd_msg_shortcut(e, cs);
		ft_irc_cmd_msg_display(e, &RB(cs)[0], 0);
		return (1);
	}
	return (0);
}
