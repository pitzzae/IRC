/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_client.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 23:07:34 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/12 19:15:33 by gtorresa         ###   ########.fr       */
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
# include <termios.h>
# include <term.h>
# include <sys/ioctl.h>

# include "libft.h"
# define FD_FREE		0
# define FD_LOCAL		1
# define FD_CLIENT		2
# define ARROW_1		27
# define ARROW_2		91
# define ARROW_UP		65
# define ARROW_DOWN		66
# define ARROW_LEFT		68
# define ARROW_RIGHT	67

# define Xv(err,res,e)		(x_void(err,res,e,__FILE__,__LINE__))
# define X(err,res,e)		(x_int(err,res,e,__FILE__,__LINE__))
# define MAX(a,b)			((a > b) ? a : b)
# define RB(a)				(e->fds[a].r_buffer)
# define BL(a)				(e->fds[a].buff_len)

# define USAGE				"Usage: %s <machine> <port> | [machine [port]]\n"
# define UND_CMD			"Undefined command: \""
# define UND_CMD_TRY		"\".  Try \"/help\".\n"
# define NO_CONN			"Connection not found !!!\nTry \"/help\".\n"
# define CMD_CONNECT		"/connect"
# define CMD_HELP			"/help"
# define CMD_NICK			"/nick"
# define CMD_USER			"/user"
# define CMD_JOIN			"/join"
# define CMD_LEAVE			"/leave"
# define CMD_WHO			"/who"
# define CMD_MSG			"/msg"
# define CMD_FILE			"/file"
# define CMD_QUIT			"/quit"

# define HELP_CMD_CONNECT	" <machine> [port]\n"
# define HELP_CMD_NICK		" <nickname>\n"
# define HELP_CMD_USER		" <user> <mode> <unused> <realname>\n"
# define HELP_CMD_CHAN		" <#chan>\n"
# define HELP_CMD_WHO		"\n"
# define HELP_CMD_MSG		" <nick>|<#chan> <message>\n"
# define HELP_CMD_FILE		" not implemented yet\n"

typedef struct		s_reply
{
	char				*arg1;
	char				*arg2;
	char				*arg3;
	char				*arg4;
}					t_reply;

typedef struct		s_term
{
	struct termios	term;
	struct termios	bterm;
	int				nb_col;
	int				nb_row;
	char			*prompt;
	int				p_len;
	int				cur;
}					t_term;

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
	char				*r_buffer;
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
	char				*host;
	int					maxfd;
	int					max;
	int					r;
	fd_set				fd_read;
	fd_set				fd_write;
	t_list				*chanel;
	struct timeval		timeout;
	t_list				*history;
	t_list				*h_pos;
	t_term				t;
	int					is_init;
	char				*state;
	int					connect;
	char				*nick;
	char				*chan;
}					t_env;

int					x_int(int err, int res, t_env *e, char *file, int line);
void				*x_void(void *err, void *res, t_env *e, char *file,
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
int					ft_init_termios(t_env *e, int i);
int					ft_reset_termios(t_env *e);
void				ft_terms_read(t_env *e, int fd);
void				ft_terminos_clean_line(t_env *e);
void				ft_client_prompt(t_env *e, int curs);
void				ft_terminos_add_char(t_env *e, int fd, char c);
void				ft_terminos_del_char(t_env *e, int fd);
void				ft_terminos_left_arrow(t_env *e, int fd);
void				ft_terminos_right_arrow(t_env *e, int fd);
void				ft_history_cmd(t_env *e, int fd, char c);
void				ft_history_cmd_add(t_env *e, char *cmd);
void				ft_history_cmd_clear(t_env *e);
int					ft_parse_irc_cmd(t_env *e, int cs);
int					ft_irc_cmd_msg(t_env *e, int cs);
int					ft_irc_cmd_join(t_env *e, int cs);
int					ft_irc_cmd_leave(t_env *e, int cs);
int					ft_irc_cmd_file(t_env *e, int cs);
int					ft_irc_cmd_nick(t_env *e, int cs);
int					ft_irc_cmd_user(t_env *e, int cs);
int					ft_irc_cmd_who(t_env *e, int cs);
int					ft_irc_cmd_quit(t_env *e, int cs, int force);
void				ft_irc_print(t_env *e, char *msg, int len, int prompt);
int					ft_irc_cmd_help(t_env *e, int cs);
size_t				ft_send(int cs, void *buff, size_t len, t_env *e);
char				*ft_parse_irc_cmd_convert(char *s, int len);
int					ft_irc_cmd_connect(t_env *e, int cs, int force);
int					client_is_connected(t_env *e);
void				ft_irc_cmd_error_arg(t_env *e, char *cmd, char *help);
void				ft_irc_update_prompt(t_env *e);
void				ft_irc_parse_return(t_env *e, int cs, int len);
char				*ft_irc_parse_reply(t_reply *r);

#endif /* !FT_IRC_CLIENT_H_ */