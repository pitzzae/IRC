/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_cmd_file_reply_ack.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <null>                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 15:23:11 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/17 17:58:20 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_server.h"

static t_ackf	*ft_irc_cmd_file_ack_user(t_env *e, int cs, t_file *f)
{
	t_list		*l;
	t_ackf		*ack;
	int			i;

	l = e->fds[cs].ack;
	while (l)
	{
		ack = l->content;
		if (ack->id == f->info.id)
		{
			i = 0;
			while (i < ack->len)
			{
				if (ack->cli[i])
				{
					ack->cli[i] = 0;
					return (ack);
				}
				i++;
			}
		}
		l = l->next;
	}
	return (NULL);
}

static int	ft_irc_cmd_file_ready_ack(t_ackf *ack)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (i < ack->len)
	{
		if (ack->cli[i] != 0)
			j++;
		i++;
	}
	if (j)
		return (j);
	return (0);
}

static int 	ft_irc_cmd_file_ready_ack_send(t_env *e, t_ackf *ack, t_file *f, int cs)
{
	uint64_t	*magic;
	t_file		*tmp_f;
	char		*tmp;

	tmp = (char*)malloc(sizeof(*tmp_f) + 8);
	ft_bzero(tmp, sizeof(*tmp_f) + 8);
	magic = ((uint64_t*)&tmp[0]);
	magic[0] = MH_MAGIC_REPLY;
	tmp_f = (t_file*)&tmp[8];
	tmp_f->info.l = 0;
	tmp_f->info.p = f->info.p;
	tmp_f->info.t = f->info.t;
	tmp_f->info.id = f->info.id;
	tmp_f->info.mod = f->info.mod;
	tmp_f->magic = MH_MAGIC_REPLY;
	ft_send(ack->fd, tmp, (size_t)e->fds[cs].buff_len, e);
	free(tmp);
	printf("send ack for next chuck to #%d len (%d)\n", ack->fd, e->fds[cs].buff_len);
	return (0);
}

int			ft_irc_cmd_file_reply_ack(t_env *e, int cs, t_file *f)
{
	int			i;
	t_ackf		*ack;

	i = 0;
	ack = NULL;
	printf("reply ack\n");
	while (i < e->maxfd)
	{
		if (e->fds[i].ack)
			ack = ft_irc_cmd_file_ack_user(e, i, f);
		if (ack)
		{
			if (ft_irc_cmd_file_ready_ack(ack) == 0)
			{
				ft_irc_cmd_file_ready_ack_send(e, ack, f, cs);
			}
			return (1);
		}
		i++;
	}
	printf("reply_ack form #%d\n", cs);
	return (1);
}