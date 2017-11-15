/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 15:42:33 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/15 11:49:13 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_client.h"

void	clean_fd(t_fd *fd)
{
	if (fd->type != FD_RFILE)
	{
		fd->type = FD_FREE;
		fd->fct_read = NULL;
		fd->fct_write = NULL;
		ft_bzero(&fd->buf_write[0], BUF_SIZE + 1);
		ft_bzero(&fd->buf_read[0], BUF_SIZE + 1);
	}
}
