/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_create_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 14:27:47 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/15 20:05:47 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_client.h"

/*TODO
 * Check stats file
 * */

static void		ft_irc_create_file_add_list(t_env *e, t_lfile *lf)
{
	if (e->wfile)
		ft_lstaddend_free(&e->wfile, ft_lstnew((void*)lf, sizeof(*lf)), u_del);
	else
		e->wfile = ft_lstnew((void*)lf, sizeof(*lf));
}

static void		ft_irc_create_file_get_info(t_lfile *lf, t_file *f)
{
	ft_strcat(lf->info.dest, f->info.dest);
	ft_strcat(lf->info.source, f->info.source);
	ft_strcat(lf->info.file_name, f->info.file_name);
	lf->info.id = f->info.id;
	lf->info.t = f->info.t;
	lf->info.l = f->info.l;
	lf->info.p = f->info.p;
}

int			ft_irc_create_file(t_env *e, t_file *f)
{
	t_lfile		lf;
	int			fd;

	ft_bzero(&lf, sizeof(lf));
	fd = open(f->info.file_name, O_CREAT | O_WRONLY, f->info.mod);
	if (fd != -1)
	{
		e->fds[fd].type = FD_WFILE;
		e->fds[fd].fct_write = NULL;
		lf.fd = fd;
		ft_irc_create_file_get_info(&lf, f);
		ft_irc_create_file_add_list(e, &lf);
		return (1);
	}
	return (0);
}
