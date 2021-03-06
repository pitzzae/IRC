/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_cmd_connect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 22:34:37 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/22 14:56:53 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_client.h"

static void	ft_irc_cmd_connect_init_fd(t_env *e, int cs)
{
	e->fds[cs].type = FD_LOCAL;
	e->fds[cs].fct_read = client_write;
	e->fds[cs].r_buffer = ft_strnew(0);
	if (e->t.prompt)
		free(e->t.prompt);
	e->t.prompt = ft_strdup("IRC$>");
	ft_irc_update_prompt(e);
	e->t.p_len = (int)ft_strlen(e->t.prompt);
	e->t.cur = (int)ft_strlen(e->t.prompt);
	e->history = NULL;
	e->h_pos = NULL;
	ft_client_prompt(e, (int)ft_strlen(e->fds[cs].r_buffer));
	e->is_init = 1;
}

static int	ft_irc_cmd_connect_parse(t_env *e, char *cmd, char *vcmd)
{
	char		**tmp;
	int			i;

	tmp = ft_strsplit(cmd, ' ');
	if (tmp[0] && tmp[1] && tmp[2] && !tmp[3])
	{
		free(tmp[0]);
		free(tmp[1]);
		free(tmp[2]);
		free(tmp);
		return (1);
	}
	else
	{
		i = 0;
		ft_irc_cmd_error_arg(e, vcmd, HELP_CMD_CONNECT);
		while (tmp[i])
			free(tmp[i++]);
		free(tmp);
		return (0);
	}
}

static void	ft_irc_cmd_connect_init(t_env *e, int cs)
{
	char			**tmp;
	int				i;

	if (ft_irc_cmd_connect_parse(e, RB(cs), CMD_CONNECT))
	{
		tmp = ft_strsplit(RB(cs), ' ');
		e->port = ft_atoi(tmp[2]);
		e->host = ft_strdup(tmp[1]);
		ft_irc_update_prompt(e);
		client_create(e, e->host, e->port);
		i = 0;
		while (tmp[i])
			free(tmp[i++]);
		free(tmp);
	}
}

static void	ft_irc_cmd_allrdy_connect(t_env *e, int cs)
{
	char			*tmp;
	uint64_t		*magic;

	tmp = ft_strjoin("All ready conencted on '", e->host);
	tmp = ft_strjoin_free(tmp, ":", 1);
	tmp = ft_strjoin_free(tmp, ft_itoa(e->port), 3);
	tmp = ft_strjoin_free(tmp, "'\n", 1);
	ft_irc_print(e, tmp, (int)ft_strlen(tmp), 0);
	free(tmp);
	tmp = malloc((int)(16 + sizeof(t_fileinfo)));
	ft_bzero(tmp, (int)(16 + sizeof(t_fileinfo)));
	magic = (uint64_t*)&tmp[0];
	magic[0] = MH_MAGIC_STOP;
	ft_send(e->sock.s, tmp, (int)(16 + sizeof(t_fileinfo)), e);
	free(tmp);
	if (e->nick)
	{
		free(e->nick);
		e->nick = NULL;
	}
	ft_irc_cmd_connect_init(e, cs);
}

int			ft_irc_cmd_connect(t_env *e, int cs, int force)
{
	if (e->connect == 1 && force == 0 && (BL(cs) > 8 && RB(cs)[8] == ' ' &&
			ft_strncmp(RB(cs), CMD_CONNECT, 8) == 0))
	{
		if (e->chan)
		{
			free(e->chan);
			e->chan = NULL;
		}
		ft_irc_cmd_allrdy_connect(e, cs);
		return (1);
	}
	else if (force == 1 || (BL(cs) > 8 && RB(cs)[8] == ' ' &&
			ft_strncmp(RB(cs), CMD_CONNECT, 8) == 0))
	{
		if (force)
			ft_irc_cmd_connect_init_fd(e, cs);
		else
		{
			ft_irc_cmd_connect_init(e, cs);
			return (1);
		}
	}
	return (0);
}
