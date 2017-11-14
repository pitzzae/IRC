/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_cmd_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 22:28:11 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/14 13:26:39 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_server.h"

/*TODO
 * Implemented FILE
 * */

int				ft_irc_cmd_file(t_env *e, int cs)
{
	t_fileinfo		*i;
	t_file			*f;

	if (e->fds[cs].buff_len > (int)(8 + sizeof(t_fileinfo)) &&
		ft_strncmp(e->fds[cs].buffer, "FILE ", 5) == 0)
	{
		f = (t_file*)&e->fds[cs].buffer[8];
		i = &f->info;
		return (1);
	}
	return (0);
}
