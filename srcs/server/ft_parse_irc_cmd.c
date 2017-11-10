/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_irc_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 15:44:59 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/10 02:01:25 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_irc_server.h"

static void	ft_split_buff_multi_cmd(t_env *e, int cs)
{
	char		**tmp;
	char		*buff_tmp;
	int			len;
	int			i;

	i = 0;
	buff_tmp = e->fds[cs].buffer;
	len = e->fds[cs].buff_len;
	tmp = ft_strsplit(e->fds[cs].buffer, '\n');
	while (tmp[i])
	{
		if (i == 0)
		{
			e->fds[cs].buffer = ft_strjoin_free(tmp[i], "\n", 1);
			e->fds[cs].buff_len = ft_strlen(e->fds[cs].buffer);
			ft_parse_irc_cmd(e, cs);
			e->fds[cs].buff_len = len - ft_strlen(e->fds[cs].buffer);
			free(e->fds[cs].buffer);
			e->fds[cs].buffer = ft_strdup(&buff_tmp[len - e->fds[cs].buff_len]);
			free(buff_tmp);
		}
		else
			free(tmp[i]);
		i++;
	}
	free(tmp);
}

static void	ft_replace_return_char(unsigned int i, char *s)
{
	(void)i;
	if (s[0] == '\r')
	{
		if (s[1] == '\n')
			s[0] = '\0';
		s[0] = '\n';
	}
}

static int	ft_irc_cmd_msg(t_env *e, int cs)
{
	t_privmsg	*msg;

	if ((e->fds[cs].buff_len >= 7 && e->fds[cs].connect &&
		ft_strncmp(e->fds[cs].buffer, "PRIVMSG", 7) == 0))
	{
		msg = ft_irc_parse_privmsg(e, cs);
		if (msg)
		{
			if (msg->dest[0] == '#')
				ft_irc_cmd_msgchanel(e, cs, msg);
			else
				ft_irc_cmd_msgpriv(e, cs, msg);
			return (1);
		}
	}
	else if (ft_strncmp(e->fds[cs].buffer, "PRIVMSG", 7) == 0)
		ft_irc_error(e, cs, "451", NOT_REGIS);
	return (0);
}

static void	ft_parse_irc_cmd_format(char *buff)
{
	int			i;
	int			len;
	int			pos;

	i = 0;
	len = ft_strlen(buff);
	while (i < len - 1)
	{
		if (buff[i] == ' ' && buff[i + 1] == ' ')
		{
			pos = 0;
			while ((i + pos) < len - 1)
			{
				buff[i + pos] = buff[i + pos + 1];
				pos++;
			}
			buff[i + pos] = '\0';
			i--;
		}
		i++;
	}
}

int			ft_parse_irc_cmd(t_env *e, int cs)
{
	ft_striteri(e->fds[cs].buffer, ft_replace_return_char);
	if (ft_strocur(e->fds[cs].buffer, '\n') > 1)
	{
		ft_split_buff_multi_cmd(e, cs);
		return (0);
	}
	ft_parse_irc_cmd_format(e->fds[cs].buffer);
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
	else if (ft_irc_cmd_chanel(e, cs))
		return (0);
	else if (ft_irc_cmd_file(e, cs))
		return (0);
	return (1);
}
