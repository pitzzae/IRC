/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_cmd_file_reply_chanel.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 14:47:43 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/17 17:58:20 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_server.h"

static void		ft_irc_cmd_file_reply_mkpk(t_env *e, int cs, t_list *l, int len)
{
	uint64_t		*magic;
	t_file			*f;

	magic = (uint64_t*)&BF(cs)[0];
	if (magic[0] == MH_MAGIC_FILE)
	{
		f = (t_file*)&BF(cs)[8];
		printf("pksend -> magic %d\n", magic[0] == MH_MAGIC_FILE);
		printf("pksend -> source: '%s'\n", f->info.source);
		printf("pksend -> dest: '%s'\n", f->info.dest);
		printf("pksend -> file_name: '%s'\n", f->info.file_name);
		printf("pksend -> pklen: '%d'\n", f->info.l);
		printf("pksend -> pose: '%d'\n", f->info.p);
		printf("pksend -> total: '%d'\n", f->info.t);
		printf("pksend -> id: '%d'\n", f->info.id);
	}
	ft_send(l->valid, BF(cs), (size_t)len, e);
}

static int	get_id_pckt(t_file *f)
{
	return f->info.id;
}

static void	reply_chanel_for_charnel(t_env *e, int cs, t_list *l, int len)
{
	size_t			i;
	t_ackf			t;
	size_t			size;

	size = ft_lstlen(l) * sizeof(int);
	t.cli = malloc(size);
	i = 0;
	while (l)
	{
		if (l->valid != cs)
		{
			t.cli[i] = l->valid;
			i++;
			ft_irc_cmd_file_reply_mkpk(e, cs, l, len);
		}
		l = l->next;
	}
	t.len = (int)i;
	t.fd = cs;
	t.id = get_id_pckt((t_file*)&BF(cs)[8]);
	l = ft_lstnew(&t, size + sizeof(t_ackf));
	((t_ackf*)(l->content))->cli = t.cli;
	if (e->fds[cs].ack)
		ft_lstaddend_free(&e->fds[cs].ack, l, u_del);
	else
		e->fds[cs].ack = l;
}

void		ft_irc_cmd_file_reply_chanel(t_env *e, int cs, char *ch, int len)
{
	t_chanel		*c;
	t_list			*l;

	l = e->chanel;
	while (l)
	{
		c = l->content;
		if (ft_strcmp(c->name, ch) == 0)
		{
			l = c->s;
			reply_chanel_for_charnel(e, cs, l, len);
			return ;
		}
		l = l->next;
	}
}
