/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_irc_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 15:44:59 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/08 02:41:01 by gtorresa         ###   ########.fr       */
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

int			ft_parse_irc_cmd(t_env *e, int cs)
{
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
	else if (ft_irc_cmd_quit(e, cs))
		return (0);
	else if (ft_irc_cmd_join(e, cs))
		return (0);
	return (1);
}