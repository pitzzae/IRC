/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_cat_infile.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 14:30:09 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/15 19:18:23 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_client.h"

/*TODO
 * check write file right
 * */

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

void		ft_irc_cat_infile(t_env *e, t_file *f)
{
	int			fd;

	fd = ft_irc_cat_infile_find_fd(e, f);
	if (fd)
		write(fd, f->msg, (size_t)f->info.l);
	e->fds[fd].type = FD_WFILE;
	e->fds[fd].fct_read = NULL;
	e->fds[fd].fct_write = NULL;
}
