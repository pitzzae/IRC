/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_cmd_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 19:53:45 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/21 14:13:56 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_client.h"

static char	*ft_irc_cmd_file_add_job(t_env *e, int cs, char *dest, char *file)
{
	char		*pck;

	pck = NULL;
	if (ft_irc_open_file(e, cs, dest, file))
		pck = (char*)ft_irc_file_make_ipacket(dest, file, "\0", 0);
	else
		ft_irc_cmd_error_arg(e, file, HELP_STATS_FILE);
	return (pck);
}

static char	*ft_irc_cmd_file_parse_argv(t_env *e, int cs, char *cmd)
{
	char		**tmp;
	char		*pck;
	int			i;

	if ((i = ft_strfocur(cmd, '\n')) >= 0)
		cmd[i] = '\0';
	tmp = ft_strsplit(cmd, ' ');
	pck = NULL;
	if (tmp[0] && tmp[1] && !tmp[2] && ft_strocur(tmp[1], '/') == 0 &&
			ft_strlen(tmp[0]) < CH_LEN && ft_strlen(tmp[1]) < CH_LEN)
		pck = ft_irc_cmd_file_add_job(e, cs, tmp[0], tmp[1]);
	else
		ft_irc_cmd_error_arg(e, CMD_FILE, HELP_CMD_FILE);
	i = 0;
	while (tmp[i])
		free(tmp[i++]);
	free(tmp);
	return (pck);
}

int			ft_irc_cmd_file(t_env *e, int cs)
{
	char		*tmp;

	if (BL(cs) > 5 && RB(cs)[5] == ' ' && ft_strncmp(RB(cs), CMD_FILE, 5) == 0)
	{
		if (e->file_rdy != 1)
			return (ft_irc_cmd_error_arg(e, CMD_FILE, NO_REGIS));
		if (BL(cs) > 6 &&
				(tmp = ft_irc_cmd_file_parse_argv(e, cs, &RB(cs)[6])) != NULL)
		{
			ft_send(e->sock.s, tmp, sizeof(t_file) + 8, e);
			free(tmp);
			ft_history_cmd_add(e, RB(cs));
		}
		return (1);
	}
	return (0);
}
