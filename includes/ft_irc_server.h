/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_server.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 23:59:00 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/22 14:58:32 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_IRC_SERVER_H
# define FT_IRC_SERVER_H

# include <signal.h>
# include <stdio.h>
# include <string.h>
# include <arpa/inet.h>
# include <netdb.h>
# include <netinet/in.h>
# include <sys/select.h>
# include <sys/socket.h>
# include <sys/resource.h>
# include <sys/time.h>
# include <sys/types.h>
# include <errno.h>
# include "libft.h"
# define FD_FREE		0
# define FD_SERV		1
# define FD_CLIENT		2
# define MAX_CMD_SIZE	4096
# define CH_LEN			20
# define MSG_FILE(bs)	((bs) - (sizeof(t_fileinfo) + 16))
# define MH_MAGIC_FILE	(uint64_t)(0xf42ef42e)
# define MH_MAGIC_MTU	(uint64_t)(0x042e042e)
# define MH_MAGIC_REPLY	(uint64_t)(0xd42ed42e)
# define MH_MAGIC_INIT	(uint64_t)(0xb42eb42e)
# define MH_MAGIC_STOP	(uint64_t)(0xe42ee42e)

# define XV(err,res,str)	(x_void(err,res,str))
# define X(err,res,str)		(x_int(err,res,str))
# define MAX(a,b)			((a > b) ? a : b)
# define BF(a)				(e->fds[a].buffer)
# define SIZE_SFILE(bs)		(16 + sizeof(t_file) - MSG_FILE((bs)))

# define USAGE			"Usage: %s port\n"
# define NICK_ERR		" :Erroneous nickname"
# define NICK_USE		" :Nickname already in use"
# define STX_ERR		" :Syntax error"
# define WEL_MSG		" :Welcome to the Internet Relay Network"
# define ALLRD_REGIS	" :Connection already registered"
# define NOT_REGIS		" :Connection not registered"
# define NO_RECIP		" :No recipient given (PRIVMSG)"
# define NO_CHANEL		" :Cannot send to channel"
# define NO_NICK		" :No such nick or channel name"
# define NO_TEXT_FOUND	" :No text to send"
# define NOT_CHAN		" :No such channel"
# define UNK_COMMAND	" :Unknown command"
# define END_NAME_LIST	" :End of NAMES list\n"
# define ERROR_CONN		"ERROR :Closing connection\n"

typedef struct		s_fileinfo
{
	char				dest[CH_LEN + 1];
	char				source[CH_LEN + 1];
	char				file_name[CH_LEN + 1];
	mode_t				mod;
	int					id;
	int					p;
	int					t;
	int					l;
}					t_fileinfo;

typedef struct		s_file
{
	t_fileinfo			info;
	char				msg[MSG_FILE(BUF_SIZE)];
	uint64_t			magic;
}					t_file;

typedef struct		s_privmsg
{
	char				*dest;
	char				*msg;
}					t_privmsg;

typedef struct		s_irc_user
{
	char				*user;
	int					mode;
	char				*realname;
}					t_irc_user;

typedef struct		s_ackf
{
	int					fd;
	int					id;
	int					*cli;
	int					len;
}					t_ackf;

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
	int					mtu_test;
	char				*tfile;
	int					tlen;
	t_list				*ack;
	char				*cmd_mtu;
	int					cmd_mtu_len;
	int					cmd;
	unsigned int		err_code;
	unsigned int		err_size;
	int					f_support;
}					t_fd;

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
void				client_buffer(t_env *e, int cs);
void				clean_fd(t_fd *fd);
int					x_int(int err, int res, char *str);
void				*x_void(void *err, void *res, char *str);
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
void				ft_irc_print_header(char *buff, t_env *e, char *code);
void				ft_irc_print_header_msg(char *buff, t_env *e, int cs);
int					ft_irc_cmd_who(t_env *e, int cs);
int					ft_irc_cmd_quit(t_env *e, int cs, int force);
int					ft_irc_cmd_join(t_env *e, int cs);
void				ft_irc_cmd_join_print(t_env *e, int cs, char *name);
int					ft_irc_cmd_leave(t_env *e, int cs);
void				ft_irc_cmd_leave_print(t_env *e, int cs, char *name);
void				ft_irc_leave(t_env *e, int cs, char *chan);
int					ft_irc_cmd_msg(t_env *e, int cs);
int					ft_irc_cmd_msgpriv(t_env *e, int cs, t_privmsg *msg);
int					ft_irc_cmd_msgchanel(t_env *e, int cs, t_privmsg *msg);
t_privmsg			*ft_irc_parse_privmsg(t_env *e, int cs);
t_chanel			*ft_irc_get_chanel(t_list *lst, char *name);
t_chanel			*ft_irc_create_chanel(t_env *e, int cs, char *name);
int					ft_irc_cmd_chanel(t_env *e, int cs);
int					ft_irc_leave_all_chan(t_env *e, int cs);
t_list				*ft_irc_clear_empty_chanel(t_list *c);
t_list				*ft_irc_chan_user_add(t_list *c, char *cname);
t_list				*ft_irc_chan_user_del(t_list *c, char *cname);
int					ft_irc_cmd_file(t_env *e, int cs);
char				*ft_irc_user_is_master_chanel(t_list *l, char *user, int f);
void				ft_irc_cmd_quit_broadcast(t_env *e, int cs, char *cmd);
int					client_read_is_magic(t_env *e, int cs, int len);
int					ft_irc_cmd_file_reply_broadcast(t_env *e, int cs,
							t_file *f);
void				ft_irc_cmd_file_reply_chanel(t_env *e, int cs,
							char *ch, int len);
int					ft_irc_cmd_file_reply_ack(t_env *e, int cs, t_file *f);
void				ft_irc_debug_show_chanel(t_list *lst);

#endif
