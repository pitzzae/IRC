/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_irc_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 19:43:46 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/11 21:41:36 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_client.h"

static void	ft_print_usage(t_env *e, char *cmd)
{
	char			*tmp;
	int				ocur;

	tmp = ft_strjoin(UND_CMD, cmd);
	ocur = ft_strfocur(tmp, '\n');
	if (ocur >= 0)
		tmp[ocur] = '\0';
	tmp = ft_strjoin_free(tmp, UND_CMD_TRY, 1);
	ft_irc_print(e, tmp, ft_strlen(tmp), 0);
	free(tmp);
}

char		*ft_parse_irc_cmd_convert(char *s, int len)
{
	char			*tmp;
	int				i;

	i = 0;
	tmp = ft_strdup(s);
	while (i < len)
	{
		tmp[i] = ft_toupper(tmp[i]);
		i++;
	}
	return (tmp);
}

int			ft_parse_irc_cmd(t_env *e, int cs)
{
	BL(cs) = ft_strlen(RB(cs));
	if (ft_irc_cmd_msg(e, cs))
		return (0);
	else if (ft_irc_cmd_nick(e, cs))
		return (0);
	else if (ft_irc_cmd_user(e, cs))
		return (0);
	else if (ft_irc_cmd_who(e, cs))
		return (0);
	else if (ft_irc_cmd_quit(e, cs, 0))
		return (0);
	else if (ft_irc_cmd_join(e, cs))
		return (0);
	else if (ft_irc_cmd_leave(e, cs))
		return (0);
	else if (ft_irc_cmd_file(e, cs))
		return (0);
	else if (ft_irc_cmd_help(e, cs))
		return (0);
	ft_print_usage(e, RB(cs));
	return (1);
}
