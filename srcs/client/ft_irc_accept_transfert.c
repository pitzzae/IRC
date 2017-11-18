/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_accept_transfert.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 17:28:09 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/17 11:48:39 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_client.h"

int		ft_irc_accept_transfert(t_env *e, t_file *f, int len)
{
	t_list	*l;
	t_lfile	*lf;

	l = e->rfile;
	while (l)
	{
		lf = l->content;
		if (ft_strncmp(f->info.source, lf->info.source, CH_LEN) == 0 &&
			ft_strncmp(f->info.dest, lf->info.dest, CH_LEN) == 0 &&
			ft_strncmp(f->info.file_name, lf->info.file_name, CH_LEN) == 0)
		{
			dprintf(7, "accept send | mtu -> %d\n", len);
			lf->send = 1;
			lf->info.t = ((int)lf->st.st_size / MSG_FILE(len - 8)) + 1;
			lf->mtu = len;
			return (1);
		}
		l = l->next;
	}
	return (0);
}
