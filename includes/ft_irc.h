/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 23:59:00 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/09 17:17:20 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_IRC_H_
# define FT_IRC_H_

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
# define FD_FREE	0
# define FD_SERV	1
# define FD_CLIENT	2
# define MAX_CMD_SIZE 4096

# define Xv(err,res,str)	(x_void(err,res,str,__FILE__,__LINE__))
# define X(err,res,str)		(x_int(err,res,str,__FILE__,__LINE__))
# define MAX(a,b)	((a > b) ? a : b)

# define USAGE		"Usage: %s port\n"

# define NICK_ERR " :Erroneous nickname"
# define STX_ERR " :Syntax error"
# define WEL_MSG " :Welcome to the Internet Relay Network"
# define ALLRD_REGIS " :Connection already registered"
# define NOT_REGIS " :Connection not registered"
# define NOT_CHAN " :No such channel"
# define ERROR_CONN "ERROR :Closing connection\n"

# define INVALID_SOCKET -1
# define SOCKET_ERROR -1
# define closesocket(s) close(s)

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

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
	char				*chanel;
	t_list				*chan_user;
}						t_fd;

typedef struct		s_sock
{
	int					s;
	struct sockaddr_in	sin;
	struct protoent		*pe;
}					t_sock;

typedef struct		s_chanel
{
	char			*name;
	char			*owner;
	t_list			*s;
}					t_chanel;

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

void				init_env(t_env *e);
void				get_opt(t_env *e, int ac, char **av);
void				main_loop(t_env *e);
void				srv_create(t_env *e, int port);
void				srv_accept(t_env *e, int s);
void				client_read(t_env *e, int cs);
void				client_write(t_env *e, int cs);
void				clean_fd(t_fd *fd);
int					x_int(int err, int res, char *str, char *file, int line);
void				*x_void(void *err, void *res, char *str, char *file,
							int line);
void				init_fd(t_env *e);
void				do_select(t_env *e);
void				check_fd(t_env *e);
size_t				ft_send(int cs, void *buff, size_t len, t_env *e);
int					ft_parse_irc_cmd(t_env *e, int cs);
int					ft_irc_cmd_user(t_env *e, int cs);
int					ft_irc_cmd_nick(t_env *e, int cs);
int					ft_irc_motd(t_env *e, int cs);
int					ft_irc_error(t_env *e, int cs, char *code, char *msg);
void				ft_irc_print(char *buff, t_env *e, int cs, char *code);
int					ft_irc_cmd_who(t_env *e, int cs);
int					ft_irc_cmd_quit(t_env *e, int cs, int force);
int					ft_irc_cmd_join(t_env *e, int cs);
int					ft_irc_cmd_leave(t_env *e, int cs);
void				ft_irc_leave(t_env *e, int cs, char *chan);
t_chanel			*ft_irc_get_chanel(t_list *lst, char *name);
t_chanel			*ft_irc_create_chanel(t_env *e, int cs, char *name);
int					ft_irc_cmd_chanel(t_env *e, int cs);
int					ft_irc_leave_all_chan(t_env *e, int cs);
t_list				*ft_irc_clear_empty_chanel(t_list *c);
t_list				*ft_irc_chan_user_add(t_list *c, char *cname);
t_list				*ft_irc_chan_user_del(t_list *c, char *cname);

void	ft_irc_debug_show_chanel(t_list *lst);

#endif /* !FT_IRC_H_ */
