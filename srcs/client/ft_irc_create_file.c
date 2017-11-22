/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_create_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 14:27:47 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/21 20:46:10 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_client.h"

static void	ft_irc_create_file_add_list(t_env *e, t_lfile *lf)
{
	if (e->wfile)
		ft_lstaddend_free(&e->wfile, ft_lstnew((void*)lf, sizeof(*lf)), u_del);
	else
		e->wfile = ft_lstnew((void*)lf, sizeof(*lf));
}

static void	ft_irc_create_file_get_info(t_lfile *lf, t_file *f)
{
	ft_strcat(lf->info.dest, f->info.dest);
	ft_strcat(lf->info.source, f->info.source);
	ft_strcat(lf->info.file_name, f->info.file_name);
	lf->info.id = f->info.id;
	lf->info.t = f->info.t;
	lf->info.l = f->info.l;
	lf->info.p = f->info.p;
}

static void	ft_irc_create_file_print(t_env *e, t_file *f)
{
	char		*msg;

	msg = ft_strjoin("Recive file '", f->info.file_name);
	msg = ft_strjoin_free(msg, "' from: '", 1);
	msg = ft_strjoin_free(msg, f->info.source, 1);
	msg = ft_strjoin_free(msg, "' size ~", 1);
	msg = ft_strjoin_free(msg, ft_itoa(f->info.l * f->info.t), 3);
	msg = ft_strjoin_free(msg, "b\n", 1);
	ft_irc_print(e, msg, (int)ft_strlen(msg), 1);
	free(msg);
}

static int	ft_irc_create_file_stats(t_env *e, t_file *f, int fd, size_t size)
{
	char		*msg;

	if (size == 0)
	{
		ft_irc_create_file_print(e, f);
		e->fds[fd].type = FD_WFILE;
		e->fds[fd].fct_write = NULL;
		return (1);
	}
	else
	{
		msg = ft_strjoin("Recive file '", f->info.file_name);
		msg = ft_strjoin_free(msg, "' [stop] /!\\ file allready exist\n", 1);
		ft_irc_print(e, msg, (int)ft_strlen(msg), 1);
		free(msg);
	}
	return (0);
}

int			ft_irc_create_file(t_env *e, t_file *f)
{
	t_lfile		lf;
	int			fd;
	struct stat	st;

	ft_bzero(&lf, sizeof(lf));
	fd = open(f->info.file_name, O_CREAT | O_WRONLY, f->info.mod);
	if (fd != -1)
	{
		if (fstat(fd, &st) == 0 &&
				ft_irc_create_file_stats(e, f, fd, (size_t)st.st_size) == 1)
			lf.fd = fd;
		else
			lf.fd = -1;
		ft_irc_create_file_get_info(&lf, f);
		ft_irc_create_file_add_list(e, &lf);
		return (1);
	}
	return (0);
}
