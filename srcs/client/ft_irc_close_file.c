/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_close_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 14:31:29 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/15 17:30:38 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_client.h"

static t_list	*ft_irc_close_file_clean_lst(t_env *e, unsigned long id)
{
	t_lfile			*lf;
	t_list			*l;
	t_list			*file;
	t_list			*tmp;

	l = e->rfile;
	file = NULL;
	while (l)
	{
		lf = l->content;
		if (lf->info.id != id)
		{
			if (file == NULL)
				file = ft_lstnew(lf, l->content_size);
			else
				ft_lstaddend_free(&file, ft_lstnew(lf, l->content_size), u_del);
		}
		tmp = l->next;
		ft_lstdelone(&l, u_del);
		l = tmp;
	}
	return (file);
}

static int		ft_irc_close_file_clean(t_env *e, unsigned long id)
{
	if (ft_lstlen(e->wfile) == 1)
	{
		ft_lstdel(&e->wfile, u_del);
		e->wfile = NULL;
	}
	else
		e->wfile = ft_irc_close_file_clean_lst(e, id);
	return (1);
}

int				ft_irc_close_file(t_env *e, t_file *f)
{
	t_lfile			*lf;
	t_list			*l;

	l = e->wfile;
	while (l)
	{
		lf = l->content;
		if (lf->info.id == f->info.id)
		{
			clean_fd(&e->fds[lf->fd]);
			close(lf->fd);
			e->fds[lf->fd].type = FD_FREE;
			e->fds[lf->fd].fct_read = NULL;
			return (ft_irc_close_file_clean(e, f->info.id));
		}
		l = l->next;
	}
	return (0);
}
