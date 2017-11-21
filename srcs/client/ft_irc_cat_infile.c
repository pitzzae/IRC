/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_cat_infile.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 14:30:09 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/17 16:42:29 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_client.h"

static int	ft_irc_cat_infile_find_fd(t_env *e, t_file *f)
{
	t_list		*l;
	t_lfile		*lf;

	l = e->wfile;
	while (l)
	{
		lf = l->content;
		if (lf->info.id == f->info.id)
			return (lf->fd);
		l = l->next;
	}
	return (-1);
}

static void	ft_irc_cat_get_next(t_env *e, int cs, t_file *f)
{
	char		*tmp;

	(void)cs;
	tmp = ft_irc_file_make_rpacket(f);
	ft_send(e->sock.s, tmp, SIZE_SFILE(f->info.l), e);
	free(tmp);
}

static void	ft_irc_cat_infile_print(t_env *e, int cs, t_file *f)
{
	char		*msg;

	msg = ft_strjoin("Chuck recive, file '", f->info.file_name);
	msg = ft_strjoin_free(msg, "' from: '", 1);
	msg = ft_strjoin_free(msg, f->info.source, 1);
	msg = ft_strjoin_free(msg, "' status ", 1);
	msg = ft_strjoin_free(msg, ft_itoa(f->info.p), 3);
	msg = ft_strjoin_free(msg, "/", 1);
	msg = ft_strjoin_free(msg, ft_itoa(f->info.t), 3);
	msg = ft_strjoin_free(msg, "\n", 1);
	ft_irc_print(e, msg, (int)ft_strlen(msg), 1);
	free(msg);
	ft_irc_cat_get_next(e, cs, f);
}

void		ft_irc_cat_infile(t_env *e, int cs, t_file *f)
{
	int			fd;

	fd = ft_irc_cat_infile_find_fd(e, f);
	if (fd)
	{
		ft_irc_cat_infile_print(e, cs, f);
		e->display_f = 1;
		write(fd, f->msg, (size_t)f->info.l);
		e->fds[fd].type = FD_WFILE;
		e->fds[fd].fct_read = NULL;
		e->fds[fd].fct_write = NULL;
	}
}
