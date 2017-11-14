/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_accept_transfert.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 17:28:09 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/14 18:21:06 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_client.h"

/*TODO
 * ft_irc_accept_transfert
 * */

int			ft_irc_accept_transfert(t_env *e, int cs, t_file *f)
{
	t_list		*l;
	t_lfile		*lf;

	(void)cs;
	l = e->file;
	while (l)
	{
		lf = l->content;
		if (ft_strncmp(f->info.source, lf->info.source, CH_LEN) == 0 &&
			ft_strncmp(f->info.dest, lf->info.dest, CH_LEN) == 0 &&
			ft_strncmp(f->info.file_name, lf->info.file_name, CH_LEN) == 0)
		{
			lf->send = 1;
			dprintf(7, "accept send: %s\n", lf->info.file_name);
			return (1);
		}
		l = l->next;
	}
	return (0);
}
