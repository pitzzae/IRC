/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_irc_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 15:44:59 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/08 19:44:45 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_irc.h"

static void	ft_split_buff_multi_cmd(t_env *e, int cs)
{
	char		**tmp;
	char		*buff_tmp;
	int			i;

	i = 0;
	buff_tmp = e->fds[cs].buffer;
	tmp = ft_strsplit(e->fds[cs].buffer, '\n');
	while (tmp[i])
	{
		e->fds[cs].buffer = ft_strjoin_free(tmp[i], "\n", 1);
		e->fds[cs].buff_len = ft_strlen(e->fds[cs].buffer);
		ft_parse_irc_cmd(e, cs);
		free(e->fds[cs].buffer);
		i++;
	}
	free(tmp);
	e->fds[cs].buffer = buff_tmp;
}

static void	ft_replace_return_char(unsigned int i, char *s)
{
	(void)i;
	if (s[0] == '\r')
	{
		if (s[0] == '\n')
			s[0] = '\0';
		s[0] = '\n';
	}
}

int			ft_parse_irc_cmd(t_env *e, int cs)
{
	t_fd		*f;

	f = &e->fds[cs];
	ft_striteri(e->fds[cs].buffer, ft_replace_return_char);
	if (ft_strocur(e->fds[cs].buffer, '\n') > 1)
	{
		ft_split_buff_multi_cmd(e, cs);
		return (0);
	}
	if (ft_irc_cmd_nick(e, cs))
		return (0);
	else if (ft_irc_cmd_user(e, cs))
		return (0);
	else if (ft_irc_cmd_who(e, cs))
		return (0);
	else if (ft_irc_cmd_quit(e, cs, 0))
		return (0);
	else if (ft_irc_cmd_join(e, cs))
		return (0);
	else if (ft_irc_cmd_chanel(e, cs))
		return (0);
	return (1);
}