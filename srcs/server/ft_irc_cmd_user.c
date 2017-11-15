/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_cmd_user.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 19:03:22 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/15 12:43:25 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_server.h"

static int		ft_irc_cmd_user_check_arg(char *cmd)
{
	char			**tmp;
	int				i;

	tmp = ft_strsplit(cmd, ' ');
	i = 0;
	while (tmp[i])
		free(tmp[i++]);
	free(tmp);
	return (i);
}

static char		*ft_irc_cmd_user_realname(char **tmp, char *buff)
{
	int				i;

	i = 3;
	while (tmp[i])
		free(tmp[i++]);
	free(tmp);
	i = ft_strnocur(buff, ' ', 3);
	if (i >= 0)
		return (ft_strdup(&buff[i + 1]));
	else
		return (ft_strdup(""));
}

static void		ft_irc_cmd_user_set(t_env *e, int cs)
{
	char			**tmp;

	tmp = ft_strsplit(&BF(cs)[5], ' ');
	e->fds[cs].user.user = tmp[0];
	if (ft_strlen(tmp[1]) == 1)
	{
		if (tmp[1][0] == '2')
			e->fds[cs].user.mode = 'w';
		else if (tmp[1][0] == '3')
			e->fds[cs].user.mode = 'i';
	}
	else
		e->fds[cs].user.mode = 0;
	free(tmp[2]);
	e->fds[cs].user.realname = ft_irc_cmd_user_realname(tmp, &BF(cs)[5]);
}

int				ft_irc_cmd_user(t_env *e, int cs)
{
	int				i;

	if (e->fds[cs].buff_len > 6 &&
		ft_strncmp(BF(cs), "USER ", 5) == 0)
	{
		e->fds[cs].argv = &BF(cs)[5];
		i = ft_strfocur(&BF(cs)[5], '\n');
		BF(cs)[i + 5] = '\0';
		if (e->fds[cs].connect == 0 && ft_strocur(&BF(cs)[5], ' ') >= 3 &&
				ft_irc_cmd_user_check_arg(&BF(cs)[5]) >= 4)
			ft_irc_cmd_user_set(e, cs);
		else if (e->fds[cs].connect == 1)
			ft_irc_error(e, cs, "462", ALLRD_REGIS);
		else
			ft_irc_error(e, cs, "461", STX_ERR);
		if (ft_strlen(&e->fds[cs].username[0]) > 0 && e->fds[cs].user.user &&
				e->fds[cs].connect == 0)
			ft_irc_motd(e, cs);
		return (1);
	}
	return (0);
}
