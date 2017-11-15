/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_send_files.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 16:07:29 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/15 02:05:24 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_client.h"

static t_list	*ft_irc_send_file_update_lst(t_env *e, int fd)
{
	t_lfile			*lf;
	t_list			*l;
	t_list			*file;
	t_list			*tmp;

	l = e->file;
	file = NULL;
	while (l)
	{
		lf = l->content;
		if (lf->fd != fd)
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

static void		ft_irc_send_file_close(t_env *e, int fd)
{
	if (ft_lstlen(e->file) == 1)
	{
		ft_lstdel(&e->file, u_del);
		e->file = NULL;
	}
	else
		e->file = ft_irc_send_file_update_lst(e, fd);
}

static int		ft_irc_send_files_data(t_env *e, int cs, t_lfile *lf)
{
	char			buff[MSG_FILE + 1];
	char			*tmp;
	int				len;

	(void)cs;
	len = (int)read(lf->fd, &buff[0], MSG_FILE);
	if (len > 0)
	{
		tmp = ft_irc_file_make_packet(lf, &buff[0], len);
		ft_send(e->sock.s, tmp, sizeof(t_file) + 8, e);
		free(tmp);
		return (0);
	}
	else
	{
		clean_fd(&e->fds[cs]);
		close(lf->fd);
		dprintf(7, "close fd '%d'\n", lf->fd);
		ft_irc_send_file_close(e, lf->fd);
		return (1);
	}
}

void			ft_irc_send_files(t_env *e, int cs)
{
	t_list			*l;
	t_lfile			*lf;

	l = e->file;
	while (l)
	{
		lf = (t_lfile*)l->content;
		if (lf->send == 1)
		{
			if (ft_irc_send_files_data(e, cs, lf) == 1)
				return ;
		}
		if (l)
			l = l->next;
	}
}
