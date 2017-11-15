/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_write_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 17:24:01 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/15 13:30:59 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_client.h"

/*TODO
 * ft_irc_write_file
 * */

int			ft_irc_write_file(t_env *e, int cs, t_file *f)
{
	(void)e;
	(void)cs;
	(void)f;
	dprintf(7, "recive data: '%s' %d/%d \n", f->info.file_name, f->info.p, f->info.t);
	dprintf(7, "id: '%lu'\n", f->info.id);
	dprintf(7, "chunck len: %d\n", f->info.l);
	return (0);
}
