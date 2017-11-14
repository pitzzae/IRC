/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_cmd_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 22:28:11 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/14 17:35:27 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_server.h"

/*TODO
 * Implemented FILE,
 * ft_irc_cmd_file_reply_broadcast
 * ft_irc_cmd_file_reply_init
 * */

static int		ft_irc_cmd_file_reply_broadcast(t_env *e, int cs, t_file *f)
{
	(void)e;
	(void)cs;
	(void)f;
	return (1);
}

static int		ft_irc_cmd_file_reply_init(t_env *e, int cs, t_file *f)
{
	(void)e;
	(void)cs;
	(void)f;
	return (1);
}

int				ft_irc_cmd_file(t_env *e, int cs)
{
	t_fileinfo		*i;
	t_file			*f;

	if (e->fds[cs].buff_len > (int)(8 + sizeof(t_fileinfo)) &&
		ft_strncmp(e->fds[cs].buffer, "FILE ", 5) == 0)
	{
		f = (t_file*)&e->fds[cs].buffer[8];
		i = &f->info;
		if (i->l >= 0 && i->l <= (int)MSG_FILE)
		{
			if (i->p == 0 && i->t == 0 && i->l == 0)
				return (ft_irc_cmd_file_reply_init(e, cs, f));
			else if (i->t > 0 && i->p <= i->t)
				return (ft_irc_cmd_file_reply_broadcast(e, cs, f));
		}
	}
	return (0);
}
