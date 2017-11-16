/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_parse_is_file.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 23:18:08 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/16 23:30:07 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_client.h"

int		ft_irc_parse_is_file(t_env *e, int cs, int len)
{
	uint64_t		*magic;
	t_fileinfo		*i;
	t_file			*f;

	if (len > (int)(8 + sizeof(t_fileinfo)))
	{
		magic = ((uint64_t*)&e->fds[cs].buf_read[0]);
		if (magic[0] == MH_MAGIC_FILE || magic[0] == MH_MAGIC_MTU)
		{
			dprintf(7, "magic header detected\n");
			f = (t_file*)&e->fds[cs].buf_read[8];
			i = &f->info;
			if (i->l >= 0 && i->l <= (int)MSG_FILE(BUF_SIZE))
			{
				if (i->p == 0 && i->t == 0 && i->l == 0)
					return (ft_irc_accept_transfert(e, f, len));
				else if (i->t > 0 && i->p <= i->t)
					return (ft_irc_write_file(e, cs, f));
			}
		}
	}
	return (0);
}
