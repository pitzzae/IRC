/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_client.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 23:07:34 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/10 16:41:11 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_IRC_CLIENT_H_
# define FT_IRC_CLIENT_H_

# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <arpa/inet.h>
# include <netdb.h>
# include <netinet/in.h>
# include <sys/select.h>
# include <sys/socket.h>
# include <sys/resource.h>
# include <errno.h>
# include "libft.h"
# define FD_FREE		0
# define FD_LOCAL		1
# define FD_CLIENT		2
# define Xv(err,res,str)	(x_void(err,res,str,__FILE__,__LINE__))
# define X(err,res,str)		(x_int(err,res,str,__FILE__,__LINE__))
# define MAX(a,b)			((a > b) ? a : b)

# define USAGE				"Usage: %s <machine> <port> | [machine [port]]\n"

typedef struct		s_privmsg
{
	char				*dest;
	char				*msg;
}					t_privmsg;

typedef struct		s_sock
{
	int					s;
	struct sockaddr_in	sin;
	struct protoent		*pe;
	struct hostent		*hi;
}					t_sock;

typedef struct		s_irc_user
{
	char				*user;
	char				*host;
	char				*srv_name;
	char				*real_user;
}					t_irc_user;

typedef struct		s_fd
{
	int					cs;
	int					type;
	void				(*fct_read)();
	void				(*fct_write)();
	void				(*fct_buffer)();
	char				buf_read[BUF_SIZE + 1];
	char				buf_write[BUF_SIZE + 1];
	char				*buffer;
	char				*argv;
	int					buff_len;
	char				username[10];
	t_irc_user			user;
	int					connect;
	char				*ipv4;
	int					b_send;
	int					b_recive;
	int					recive;
	char				*chanel;
	t_list				*chan_user;
}						t_fd;

typedef struct		s_env
{
	char				*hostname;
	t_fd				*fds;
	t_sock				sock;
	int					port;
	int					maxfd;
	int					max;
	int					r;
	fd_set				fd_read;
	fd_set				fd_write;
	t_list				*chanel;
	struct timeval		timeout;
}					t_env;

int					x_int(int err, int res, char *str, char *file, int line);
void				*x_void(void *err, void *res, char *str, char *file,
							int line);
void				init_env(t_env *e);
void				get_opt(t_env *e, int ac, char **av);
void				main_loop(t_env *e);
void				client_create(t_env *e, char *ip, int port);
void				client_read(t_env *e, int cs);
void				client_write(t_env *e, int cs);
void				clean_fd(t_fd *fd);
void				init_fd(t_env *e);
void				do_select(t_env *e);
void				check_fd(t_env *e);

#endif /* !FT_IRC_CLIENT_H_ */