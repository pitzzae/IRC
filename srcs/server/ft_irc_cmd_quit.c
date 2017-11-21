/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_cmd_quit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 23:10:12 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/21 14:13:56 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_server.h"

static char	*ft_format_bsr(int b)
{
	char		*tmp;

	if (b > 1000)
	{
		tmp = ft_itoa(b / 1000);
		tmp = ft_strjoin_free(tmp, " kb", 1);
	}
	else
	{
		tmp = ft_strnew(5);
		ft_bzero(tmp, 5);
		ft_strcat(tmp, "0.");
		if (b < 100)
			ft_strcat(tmp, "0");
		if (b < 10)
			ft_strcat(tmp, "0");
		tmp = ft_strjoin_free(tmp, ft_itoa(b), 3);
		tmp = ft_strjoin_free(tmp, " kb", 1);
	}
	return (tmp);
}

static void	ft_irc_cmd_quit_stats(t_env *e, int cs, char *buff)
{
	char		*tmp;

	ft_irc_print(buff, e, cs, "NOTICE");
	ft_strcat(buff, ":Connection statistics: client ");
	tmp = ft_format_bsr(e->fds[cs].b_send);
	ft_strcat(buff, tmp);
	free(tmp);
	ft_strcat(buff, ", server ");
	tmp = ft_format_bsr(e->fds[cs].b_recive);
	ft_strcat(buff, tmp);
	free(tmp);
	ft_strcat(buff, ".\n");
}

static void	ft_irc_quit_clean_chanel(t_env *e, int cs)
{
	ft_irc_leave_all_chan(e, cs);
	free(e->fds[cs].chanel);
	e->fds[cs].chanel = NULL;
}

static void	ft_irc_cmd_quit_processing(t_env *e, int cs, char *buff)
{
	ft_strcat(buff, ERROR_CONN);
	ft_send(cs, buff, ft_strlen(buff), e);
	clean_fd(&e->fds[cs]);
	if (e->fds[cs].chan_user)
		ft_irc_quit_clean_chanel(e, cs);
	free(e->fds[cs].user.user);
	free(e->fds[cs].user.realname);
	free(e->fds[cs].buffer);
	e->fds[cs].buff_len = 0;
	e->fds[cs].buffer = NULL;
	close(cs);
	printf("client #%d quit\n", cs);
}

int			ft_irc_cmd_quit(t_env *e, int cs, int force)
{
	char		buff[1024];

	ft_bzero(buff, 1024);
	if (force == 1 || (e->fds[cs].buff_len > 4 &&
		ft_strncmp(e->fds[cs].buffer, "QUIT", 4) == 0))
	{
		if (e->fds[cs].connect == 1)
		{
			ft_irc_cmd_quit_broadcast(e, cs, &e->fds[cs].buffer[4]);
			ft_irc_cmd_quit_stats(e, cs, &buff[0]);
		}
		else
			ft_bzero(buff, ft_strlen(ERROR_CONN) + 1);
		ft_irc_cmd_quit_processing(e, cs, buff);
		return (1);
	}
	return (0);
}
