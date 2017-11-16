/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_open_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 14:47:16 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/15 14:09:26 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_client.h"

static int	ft_irc_open_file_set_fdsize(t_lfile *lf, int fd)
{
	lf->fd = fd;
	if (fstat(fd, &lf->st) == 0)
	{
		lf->fd = fd;
		lf->info.p = 0;
		lf->info.t = ((int)lf->st.st_size / MSG_FILE(BUF_SIZE)) + 1;
		lf->send = 0;
		lf->info.id = ft_make_id();
		return (1);
	}
	close(fd);
	return (0);
}

static void	ft_irc_open_file_set_info(t_fileinfo *info,
										char *dest, char *file, char *user)
{
	char		*tmp;
	int			i;

	i = ft_strlocur(file, '/');
	tmp = file;
	if (i >= 0 && file[i + 1])
		tmp = &file[i + 1];
	ft_strcat(info->dest, dest);
	ft_strcat(info->file_name, tmp);
	ft_strcat(info->source, user);
}

static void	ft_irc_open_file_add_list(t_env *e, t_lfile *lf)
{
	if (e->rfile)
		ft_lstaddend_free(&e->rfile, ft_lstnew((void*)lf, sizeof(*lf)), u_del);
	else
		e->rfile = ft_lstnew((void*)lf, sizeof(*lf));
}

int			ft_irc_open_file(t_env *e, int cs, char *dest, char *file)
{
	t_lfile		lf;
	int			fd;

	(void)cs;
	ft_bzero(&lf, sizeof(lf));
	fd = open(file, O_RDONLY);
	if (ft_irc_open_file_set_fdsize(&lf, fd))
	{
		e->fds[fd].type = FD_RFILE;
		e->fds[fd].fct_read = ft_irc_send_files;
		ft_irc_open_file_set_info(&lf.info, dest, file, e->nick);
		ft_irc_open_file_add_list(e, &lf);
		return (1);
	}
	else
		close(fd);
	return (0);
}
