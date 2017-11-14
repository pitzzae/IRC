/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_send_files.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 16:07:29 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/14 16:32:11 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_client.h"

/*TODO
 * free and close fd on EOF
 * */

static void		ft_irc_send_files_data(t_env *e, t_lfile *lf)
{
	char			buff[MSG_FILE + 1];
	char			*tmp;
	int				len;

	len = read(lf->fd, &buff[0], MSG_FILE);
	if (len > 0)
	{
		tmp = ft_irc_file_make_packet(lf, &buff[0], len);
		ft_send(e->sock.s, tmp, sizeof(t_file) + 8, e);
	}
	else
	{
		//free, close
	}
}

void			ft_irc_send_files(t_env *e)
{
	t_list			*l;
	t_lfile			*lf;

	l = e->file;
	while (l)
	{
		lf = (t_lfile*)l->content;
		if (lf->send == 1)
		{
			ft_irc_send_files_data(e, lf);
		}
		l = l->next;
	}
}
