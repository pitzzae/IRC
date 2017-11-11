/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_cmd_connect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 22:34:37 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/11 23:21:52 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_client.h"

static void		ft_irc_cmd_connect_init_fd(t_env *e, int cs)
{
	e->fds[cs].type = FD_LOCAL;
	e->fds[cs].fct_read = client_write;
	e->fds[cs].r_buffer = ft_strnew(0);
	e->t.prompt = ft_strdup("IRC$>");
	e->t.p_len = ft_strlen(e->t.prompt);
	e->t.cur = ft_strlen(e->t.prompt);
	e->history = NULL;
	e->h_pos = NULL;
	e->connect = 0;
	ft_client_prompt(e, ft_strlen(e->fds[cs].r_buffer));
	e->is_init = 1;
}

static void	ft_irc_cmd_allrdy_connect(t_env *e)
{
	char			*tmp;

	tmp = ft_strjoin("All ready conencted on '", e->host);
	tmp = ft_strjoin_free(tmp, ":", 1);
	tmp = ft_strjoin_free(tmp, ft_itoa(e->port), 3);
	tmp = ft_strjoin_free(tmp, "'\n", 1);
	ft_irc_print(e, tmp, ft_strlen(tmp), 0);
	free(tmp);
}

int			ft_irc_cmd_connect(t_env *e, int cs, int force)
{
	char			**tmp;

	if (e->connect == 1)
	{
		ft_irc_cmd_allrdy_connect(e);
		return (1);
	}
	else if ((BL(cs) > 8 && ft_strncmp(RB(cs), "/connect", 8) == 0) || force == 1)
	{
		if (force)
			ft_irc_cmd_connect_init_fd(e, cs);
		else
		{
			if (ft_strocur(RB(cs), ' ') == 2)
			{
				tmp = ft_strsplit(RB(cs), ' ');
				e->port = atoi(tmp[2]);
				e->host = tmp[1];
				client_create(e, e->host, e->port);
				return (1);
			}
		}
	}
	return (0);
}