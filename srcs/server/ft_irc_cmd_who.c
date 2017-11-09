/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_cmd_who.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 19:06:28 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/07 23:05:09 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.h"

static char	*ft_irc_who_chan(t_env *e, int cs)
{
	char		*tmp = "*";

	(void)e;
	(void)cs;
	return (tmp);
}

static char	*ft_irc_who_user(t_env *e, int cs, char *buff)
{
	ft_irc_print(buff, e, cs, "352");
	ft_strcat(buff, ft_irc_who_chan(e, cs));
	ft_strcat(buff, " ~");
	ft_strcat(buff, e->fds[cs].user.user);
	ft_strcat(buff, " ");
	ft_strcat(buff, e->fds[cs].ipv4);
	ft_strcat(buff, " ");
	ft_strcat(buff, e->hostname);
	ft_strcat(buff, " ");
	ft_strcat(buff, e->fds[cs].username);
	ft_strcat(buff, " H :0 ");
	ft_strcat(buff, e->fds[cs].user.real_user);
	ft_strcat(buff, "\n");
	return (buff);
}

static void	ft_irc_cmd_return(t_env *e, int cs, char *who, char *buff)
{
	ft_irc_print(buff, e, cs, "315");
	ft_strcat(buff, "* :End of WHO list\n");
	who = ft_strjoin_free(who, buff, 1);
	ft_send(cs, who, ft_strlen(who), e);
	free(who);
}

int			ft_irc_cmd_who(t_env *e, int cs)
{
	char		buff[1024];
	char		*who;
	int			i;

	if (e->fds[cs].buff_len > 3 &&
		ft_strncmp(e->fds[cs].buffer, "WHO", 3) == 0)
	{
		i = ft_strfocur(&e->fds[cs].buffer[0], '\n');
		e->fds[cs].buffer[i] = '\0';
		e->fds[cs].argv = &e->fds[cs].buffer[4];
		i = 0;
		who = ft_strnew(0);
		while (i < e->maxfd)
		{
			if ((e->fds[i].type == FD_CLIENT) && e->fds[i].connect == 1) {
				who = ft_strjoin_free(who, ft_irc_who_user(e, i, &buff[0]), 1);
			}
			i++;
		}
		ft_irc_cmd_return(e, cs, who, &buff[0]);
		return (1);
	}
	return (0);
}