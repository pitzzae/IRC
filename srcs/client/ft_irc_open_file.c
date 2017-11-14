/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_open_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 14:47:16 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/14 16:29:35 by gtorresa         ###   ########.fr       */
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
		lf->info.t = ((int)lf->st.st_size / MSG_FILE) + 1;
		lf->send = 0;
		return (1);
	}
	return (0);
}

static void	ft_irc_open_file_set_info(t_fileinfo *info, char *dest, char *file)
{
	char		*tmp;
	int			i;

	i = ft_strlocur(file, '/');
	tmp = file;
	if (i >= 0 && file[i + 1])
		tmp = &file[i + 1];
	ft_strncat(info->dest, dest, CH_LEN);
	ft_strncat(info->file_name, tmp, CH_LEN);
}

static void	ft_irc_open_file_add_list(t_env *e, t_lfile *lf)
{
	if (e->file)
		ft_lstaddend_free(&e->file, ft_lstnew((void*)lf, sizeof(*lf)), u_del);
	else
		e->file = ft_lstnew((void*)lf, sizeof(*lf));
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
		ft_irc_open_file_set_info(&lf.info, dest, file);
		ft_irc_open_file_add_list(e, &lf);
		return (1);
	}
	else
		close(fd);
	return (0);
}
