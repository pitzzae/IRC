/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_file_make_packet.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 13:50:13 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/14 21:17:52 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_client.h"

static void	ft_irc_file_info(t_fileinfo *info, char *dest, char *file)
{
	ft_strcat(info->dest, dest);
	ft_strcat(info->file_name, file);
	info->p = 0;
	info->t = 0;
}

void		*ft_irc_file_make_ipacket(char *dest, char *file, void *d, int len)
{
	uint64_t	*magic;
	t_file		*f;
	char		*tmp;

	tmp = (char*)malloc(sizeof(*f) + 8);
	ft_bzero(tmp, sizeof(*f) + 8);
	magic = ((uint64_t*)&tmp[0]);
	magic[0] = MH_MAGIC_FILE;
	f = (t_file*)&tmp[8];
	ft_irc_file_info(&f->info, dest, file);
	ft_memcpy(f->msg, d, (size_t)len);
	f->info.l = len;
	return ((void*)tmp);
}

void		*ft_irc_file_make_packet(t_lfile *lf, char *buff, int len)
{
	uint64_t	*magic;
	t_file		*f;
	char		*tmp;

	tmp = (char*)malloc(sizeof(*f) + 8);
	ft_bzero(tmp, sizeof(*f) + 8);
	magic = ((uint64_t*)&tmp[0]);
	magic[0] = MH_MAGIC_FILE;
	f = (t_file*)&tmp[8];
	ft_irc_file_info(&f->info, lf->info.dest, lf->info.file_name);
	lf->info.p++;
	f->info.p = lf->info.p;
	f->info.t = lf->info.t;
	ft_memcpy(f->msg, buff, (size_t)len);
	f->info.l = len;
	return ((void*)tmp);
}
