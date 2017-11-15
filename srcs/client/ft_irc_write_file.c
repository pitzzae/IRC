/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_write_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 17:24:01 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/15 17:29:33 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_client.h"

int			ft_irc_write_file(t_env *e, t_file *f)
{
	if (f->info.p == 1)
		ft_irc_create_file(e, f);
	ft_irc_cat_infile(e, f);
	if (f->info.p == f->info.t)
		ft_irc_close_file(e, f);
	return (1);
}
