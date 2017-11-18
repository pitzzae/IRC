/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_cmd_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 22:28:11 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/17 19:10:00 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_server.h"

/*TODO
 * Remove debug
 * */

static int		ft_irc_cmd_file_reply_init(t_env *e, int cs, t_file *f)
{
	ft_bzero(f->info.source, CH_LEN + 1);
	ft_strcat(f->info.source, e->fds[cs].username);
	ft_send(cs, e->fds[cs].buffer, (size_t)e->fds[cs].buff_len, e);
	return (1);
}

static void		ft_irc_cmd_file_is_truck(t_env *e, int cs)
{
	char			*tmp;

	if (e->fds[cs].tfile)
	{
		printf("is_truck add prev data\n");
		tmp = ft_strnew((size_t)e->fds[cs].buff_len + e->fds[cs].tlen);
		ft_memcpy(tmp, e->fds[cs].tfile, (size_t)e->fds[cs].tlen);
		ft_memcpy(&tmp[e->fds[cs].tlen], BF(cs), (size_t)e->fds[cs].buff_len);
		e->fds[cs].buff_len += e->fds[cs].tlen;
		free(e->fds[cs].buffer);
		e->fds[cs].buffer = tmp;
		free(e->fds[cs].tfile);
		e->fds[cs].tfile = NULL;
		e->fds[cs].tlen = 0;
	}
}

int				ft_irc_cmd_file(t_env *e, int cs)
{
	uint64_t		*magic;
	t_fileinfo		*i;
	t_file			*f;

	ft_irc_cmd_file_is_truck(e, cs);
	printf("%d %d | %d\n",e->fds[cs].buff_len, (int)(8 + sizeof(t_fileinfo)), e->fds[cs].buff_len > (int)(8 + sizeof(t_fileinfo)));
	if (e->fds[cs].buff_len > (int)(8 + sizeof(t_fileinfo)))
	{
		magic = ((uint64_t*)&e->fds[cs].buffer[0]);
		if (magic[0] == MH_MAGIC_FILE || magic[0] == MH_MAGIC_MTU || magic[0] == MH_MAGIC_REPLY)
		{
			printf("magic if MH_MAGIC_FILE  = %d\n", magic[0] == MH_MAGIC_FILE);
			printf("magic if MH_MAGIC_MTU   = %d\n", magic[0] == MH_MAGIC_MTU);
			printf("magic if MH_MAGIC_REPLY = %d\n", magic[0] == MH_MAGIC_REPLY);
			f = (t_file*)&e->fds[cs].buffer[8];
			i = &f->info;
			printf("pksend -> MSG_FILE: '%d'\n", (int)MSG_FILE(BUF_SIZE));
			printf("pksend -> source: '%s'\n", f->info.source);
			printf("pksend -> dest: '%s'\n", f->info.dest);
			printf("pksend -> file_name: '%s'\n", f->info.file_name);
			printf("pksend -> pklen: '%d'\n", f->info.l);
			printf("pksend -> pose: '%d'\n", f->info.p);
			printf("pksend -> total: '%d'\n", f->info.t);
			printf("pksend -> id: '%d'\n", f->info.id);
			if (magic[0] == MH_MAGIC_REPLY)
				return (ft_irc_cmd_file_reply_ack(e, cs, f));
			if (i->l >= 0 && i->l <= (int)MSG_FILE(BUF_SIZE))
			{
				if (i->p == 0 && i->t == 0 && i->l == 0)
				{
					printf("ft_irc_cmd_file_reply_init\n");
					return (ft_irc_cmd_file_reply_init(e, cs, f));
				}
				else if (i->t > 0 && i->p <= i->t)
				{
					printf("ft_irc_cmd_file_reply_broadcast\n");
					return (ft_irc_cmd_file_reply_broadcast(e, cs, f));
				}
			}
			return (1);
		}
	}
	return (0);
}
