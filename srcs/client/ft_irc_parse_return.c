/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_parse_return.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 12:45:10 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/15 17:29:55 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_client.h"

static t_reply	*ft_irc_parse_return_2(char *msg)
{
	t_reply			*r;
	int				i;

	r = NULL;
	i = (int)ft_strocur(msg, ' ');
	if (i == 2)
	{
		r = malloc(sizeof(*r));
		r->arg1 = msg;
		i = ft_strfocur(r->arg1, ' ');
		r->arg1[i] = '\0';
		r->arg2 = &r->arg1[i + 1];
		i = ft_strfocur(r->arg2, ' ');
		r->arg2[i] = '\0';
		r->arg3 = &r->arg2[i + 1];
		r->arg4 = NULL;
	}
	return (r);
}

static t_reply	*ft_irc_parse_return_3(char *msg)
{
	t_reply			*r;
	int				i;

	r = NULL;
	i = (int)ft_strocur(msg, ' ');
	if (i >= 3)
	{
		r = malloc(sizeof(*r));
		r->arg1 = msg;
		i = ft_strfocur(r->arg1, ' ');
		r->arg1[i] = '\0';
		r->arg2 = &r->arg1[i + 1];
		i = ft_strfocur(r->arg2, ' ');
		r->arg2[i] = '\0';
		r->arg3 = &r->arg2[i + 1];
		i = ft_strfocur(r->arg3, ' ');
		r->arg3[i] = '\0';
		r->arg4 = &r->arg3[i + 1];
	}
	return (r);
}

static void		ft_irc_parse_return_multi(t_env *e, char *cmd)
{
	t_reply			*r;
	char			*msg;

	r = ft_irc_parse_return_2(cmd);
	if (!r)
		r = ft_irc_parse_return_3(cmd);
	msg = NULL;
	if (r)
	{
		msg = ft_irc_parse_reply(e, r);
		free(r);
	}
	if (msg)
	{
		ft_irc_print(e, msg, (int)ft_strlen(msg), 1);
		free(msg);
	}
}

static int		ft_irc_parse_is_file(t_env *e, int cs, int len)
{
	uint64_t		*magic;
	t_fileinfo		*i;
	t_file			*f;

	if (len > (int)(8 + sizeof(t_fileinfo)))
	{
		magic = ((uint64_t*)&e->fds[cs].buf_read[0]);
		if (magic[0] == MH_MAGIC_FILE)
		{
			f = (t_file*)&e->fds[cs].buf_read[8];
			i = &f->info;
			if (i->l >= 0 && i->l <= (int)MSG_FILE)
			{
				if (i->p == 0 && i->t == 0 && i->l == 0)
					return (ft_irc_accept_transfert(e, f));
				else if (i->t > 0 && i->p <= i->t)
					return (ft_irc_write_file(e, f));
			}
		}
	}
	return (0);
}

void			ft_irc_parse_return(t_env *e, int cs, int len)
{
	char			**tmp;
	int				i;

	if (len > 0)
	{
		if (!ft_irc_parse_is_file(e, cs, len))
		{
			i = 0;
			tmp = ft_strsplit(e->fds[cs].buf_read, '\n');
			while (tmp[i])
			{
				ft_irc_parse_return_multi(e, tmp[i]);
				free(tmp[i]);
				i++;
			}
			free(tmp);
		}
	}
	ft_bzero(e->fds[cs].buf_read, (size_t)len);
}
