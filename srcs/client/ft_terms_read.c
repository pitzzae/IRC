/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_terms_read.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 12:21:13 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/11 17:28:05 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_client.h"

static void	ft_terms_clear_buffer(t_env *e, char *buff)
{
	struct winsize	win;

	ioctl(0, TIOCGWINSZ, &win);
	e->t.nb_col = win.ws_col;
	e->t.nb_row = win.ws_row;
	ft_bzero(buff, 7);
}

static int	ft_terms_buffer_char_value(char *buff, int start, int stop, char c)
{
	int				i;

	i = start;
	while (i < stop)
	{
		if (buff[i] != c)
			return (0);
		i++;
	}
	return (1);
}

static void	ft_terms_buffer_arrow(t_env *e, int fd, char *buff)
{
	if (buff[2] == ARROW_LEFT)
		ft_terminos_left_arrow(e, fd);
	else if (buff[2] == ARROW_RIGHT)
		ft_terminos_right_arrow(e, fd);
	else if (buff[2] == ARROW_UP || buff[2] == ARROW_DOWN)
		ft_history_cmd(e, fd, buff[2]);
}

static void	ft_terms_buffer_char(t_env *e, int fd, char *buff)
{
	char			c;

	c = buff[0];
	if (buff[0] == buff[1] && (ft_terms_buffer_char_value(buff, 2, 5, 0)))
	{
		if (c == 10)
			c = '\n';
		if (c == 127 && e->t.cur > e->t.p_len)
			ft_terminos_del_char(e, fd);
		else if (c != 127)
			ft_terminos_add_char(e, fd, c);
	}
	else if (buff[0] == ARROW_1 && buff[1] == ARROW_2)
		ft_terms_buffer_arrow(e, fd, buff);
}

void		ft_terms_read(t_env *e, int fd)
{
	char			buff[7];
	char			c;
	int				len;

	ft_terms_clear_buffer(e, &buff[0]);
	len = read(fd, &buff, 6);
	if (len > 0)
	{
		c = buff[0];
		ft_strncat(buff, &c, 1);
		dprintf(7, "%d %d %d %d %d %d\n", buff[0], buff[1], buff[2], buff[3], buff[4], buff[5]);
		dprintf(7, "[s] e->t.cur %d e->t.p_len %d\n", e->t.cur, e->t.p_len);
		ft_terms_buffer_char(e, fd, &buff[0]);
		dprintf(7, "[x] e->t.cur %d e->t.p_len %d\n", e->t.cur, e->t.p_len);
	}
}
