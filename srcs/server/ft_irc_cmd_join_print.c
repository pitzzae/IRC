/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_cmd_join_print.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:57:49 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/09 18:54:53 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.h"

static char	*ft_irc_cmd_join_user_chanel_print(char *owner, char *s1, char *s2)
{
	if (ft_strlen(s1) > 0)
		s1 = ft_strjoin_free(s1, " ", 1);
	if (ft_strcmp(owner, s2) == 0)
		s1 = ft_strjoin_free(s1, "@", 1);
	s1 = ft_strjoin_free(s1, s2, 1);
	return (s1);
}

static char	*ft_irc_cmd_join_user_chanel(t_env *e, char *name)
{
	t_chanel		*c;
	t_list			*l;
	char			*tmp;

	l = e->chanel;
	tmp = ft_strnew(0);
	while (l)
	{
		c = l->content;
		if (ft_strcmp(c->name, name) == 0)
		{
			l = c->s;
			while (l)
			{
				tmp = ft_irc_cmd_join_user_chanel_print(c->owner,
						tmp, e->fds[l->valid].username);
				l = l->next;
			}
			return (tmp);
		}
		l = l->next;
	}
	return (tmp);
}

static void	ft_irc_cmd_join_print_chanel(t_env *e, int cs, char *name, char *b)
{
	char			*tmp;

	ft_irc_print_header(b, e, "353");
	ft_strcat(b, e->fds[cs].username);
	ft_strcat(b, " = ");
	ft_strcat(b, name);
	ft_strcat(b, " :");
	tmp = ft_irc_cmd_join_user_chanel(e, name);
	ft_strcat(b, tmp);
	free(tmp);
	ft_strcat(b, "\n");
}

static void	ft_irc_cmd_join_broadcast(t_env *e, char *buff, int cs, char *cname)
{
	t_list			*l;
	t_chanel		*c;

	l = e->chanel;
	while (l)
	{
		c = l->content;
		if (ft_strcmp(c->name, cname) == 0)
		{
			l = c->s;
			while (l)
			{
				if (cs != l->valid)
					ft_send(l->valid, buff, ft_strlen(buff), e);
				l = l->next;
			}
			return ;
		}
		l = l->next;
	}
}

void		ft_irc_cmd_join_print(t_env *e, int cs, char *name)
{
	char			buff[1024];

	ft_bzero(buff, 1024);
	ft_strcat(buff, ":");
	ft_strcat(buff, e->fds[cs].username);
	ft_strcat(buff, "!~");
	ft_strcat(buff, e->fds[cs].user.user);
	ft_strcat(buff, "@");
	ft_strcat(buff, e->fds[cs].ipv4);
	ft_strcat(buff, " JOIN :");
	ft_strcat(buff, name);
	ft_strcat(buff, "\n");
	ft_irc_cmd_join_print_chanel(e, cs, name, &buff[ft_strlen(buff) - 1]);
	ft_irc_print_header(buff, e, "366");
	ft_strcat(buff, e->fds[cs].username);
	ft_strcat(buff, " ");
	ft_strcat(buff, name);
	ft_strcat(buff, END_NAME_LIST);
	ft_send(cs, buff, ft_strlen(buff), e);
	buff[ft_strfocur(buff, '\n') + 1] = '\0';
	ft_irc_cmd_join_broadcast(e, buff, cs, name);
}
