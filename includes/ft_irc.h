/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <null>                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 23:59:00 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/06 00:07:50 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_IRC_H_
# define FT_IRC_H_

# include <sys/select.h>
# include <stdio.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <stdlib.h>
# include <netdb.h>
# include <netinet/in.h>
# include <unistd.h>
# include <sys/socket.h>
# include <sys/resource.h>
# include <string.h>
# include <sys/select.h>
# include <errno.h>
# include "libft.h"
# define FD_FREE	0
# define FD_SERV	1
# define FD_CLIENT	2

# define Xv(err,res,str)	(x_void(err,res,str,__FILE__,__LINE__))
# define X(err,res,str)		(x_int(err,res,str,__FILE__,__LINE__))
# define MAX(a,b)	((a > b) ? a : b)

# define USAGE		"Usage: %s port\n"

# define INVALID_SOCKET -1
# define SOCKET_ERROR -1
# define closesocket(s) close(s)

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

typedef struct	s_fd
{
	int	type;
	void	(*fct_read)();
	void	(*fct_write)();
	char	buf_read[BUF_SIZE + 1];
	char	buf_write[BUF_SIZE + 1];
}		t_fd;

typedef struct	s_env
{
	t_fd		*fds;
	int		port;
	int		maxfd;
	int		max;
	int		r;
	fd_set	fd_read;
	fd_set	fd_write;
}		t_env;

void	init_env(t_env *e);
void	get_opt(t_env *e, int ac, char **av);
void	main_loop(t_env *e);
void	srv_create(t_env *e, int port);
void	srv_accept(t_env *e, int s);
void	client_read(t_env *e, int cs);
void	client_write(t_env *e, int cs);
void	clean_fd(t_fd *fd);
int		x_int(int err, int res, char *str, char *file, int line);
void	*x_void(void *err, void *res, char *str, char *file, int line);
void	init_fd(t_env *e);
void	do_select(t_env *e);
void	check_fd(t_env *e);

#endif /* !FT_IRC_H_ */
