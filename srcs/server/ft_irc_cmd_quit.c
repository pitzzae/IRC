/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_cmd_quit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 23:10:12 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/07 23:53:15 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.h"

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
	t_fd		f;

	f = e->fds[cs];
	ft_irc_print(buff, e, cs, 0);
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

int			ft_irc_cmd_quit(t_env *e, int cs)
{
	char		buff[1024];

	if (e->fds[cs].buff_len == 5 &&
		ft_strncmp(e->fds[cs].buffer, "QUIT", 4) == 0)
	{
		if (e->fds[cs].connect == 1)
			ft_irc_cmd_quit_stats(e, cs, &buff[0]);
		else
			ft_bzero(buff, ft_strlen(ERROR_CONN) + 1);
		ft_strcat(buff, ERROR_CONN);
		ft_send(cs, buff, ft_strlen(buff), e);
		free(e->fds[cs].user.user);
		free(e->fds[cs].user.host);
		free(e->fds[cs].user.real_user);
		free(e->fds[cs].user.srv_name);
		close(cs);
		clean_fd(&e->fds[cs]);
		printf("client #%d quit\n", cs);
		return (1);
	}
	return (0);
}