/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_parse_is_file.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 23:18:08 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/18 15:40:28 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_client.h"

static void	ft_irc_parse_is_file_argreg(t_env *e, int cs)
{
	char			*tmp;

	if (e->fds[cs].tfile)
	{
		tmp = ft_strnew((size_t)e->fds[cs].r + e->fds[cs].tlen);
		ft_memcpy(tmp, e->fds[cs].tfile, (size_t)e->fds[cs].tlen);
		ft_memcpy(&tmp[e->fds[cs].tlen + 1], RB(cs), (size_t)e->fds[cs].r);
		e->fds[cs].r += e->fds[cs].tlen;
		free(RB(cs));
		RB(cs) = tmp;
		free(e->fds[cs].tfile);
		e->fds[cs].tfile = NULL;
		e->fds[cs].tlen = 0;
	}
}

static int	ft_irc_parse_is_file_mreply(t_env *e, t_file *f)
{
	t_list			*l;
	t_lfile			*lf;

	l = e->rfile;
	while (l)
	{
		lf = l->content;
		if (lf->info.id == f->info.id)
		{
			lf->send = 1;
			return (1);
		}
		l = l->next;
	}
	return (0);
}

static int	ft_irc_parse_is_file_1(t_env *e, int cs, int len)
{
	uint64_t		*magic;
	t_fileinfo		*i;
	t_file			*f;

	magic = ((uint64_t*)&RB(cs)[0]);
	f = (t_file*)&RB(cs)[8];
	i = &f->info;
	if (magic[0] == MH_MAGIC_REPLY)
		return (ft_irc_parse_is_file_mreply(e, f));
	if (i->l >= 0 && i->l <= (int)MSG_FILE(BUF_SIZE))
	{
		if (i->p == 0 && i->t == 0 && i->l == 0)
			return (ft_irc_accept_transfert(e, f, len));
		else if (i->t > 0 && i->p <= i->t)
			return (ft_irc_write_file(e, cs, f));
	}
	return (0);
}

int			ft_irc_parse_is_file(t_env *e, int cs, int len)
{
	uint64_t		*magic;

	if (len > (int)(8 + sizeof(t_fileinfo)))
	{
		RB(cs) = ft_strnew((size_t)len);
		ft_memcpy(RB(cs), &e->fds[cs].buf_read[0], (size_t)len);
		ft_irc_parse_is_file_argreg(e, cs);
		magic = ((uint64_t*)&RB(cs)[0]);
		if (magic[0] == MH_MAGIC_FILE || magic[0] == MH_MAGIC_MTU ||
				magic[0] == MH_MAGIC_REPLY)
			return (ft_irc_parse_is_file_1(e, cs, len));
	}
	return (0);
}
