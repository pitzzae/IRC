/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_terminos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 18:26:01 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/21 14:13:56 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_client.h"

int			ft_init_termios(t_env *e, int i)
{
	struct winsize		win;

	if (tgetent(NULL, getenv("TERM")) < 1)
	{
		ft_putstr_fd("error: env TERM not set\n", 2);
		return (0);
	}
	if (tcgetattr(0, &(e->t.term)) == -1)
		return (0);
	if (i == 1 && tcgetattr(0, &(e->t.bterm)) == -1)
		return (0);
	e->t.term.c_lflag &= ~(ICANON | ECHO);
	e->t.term.c_cc[VMIN] = 1;
	e->t.term.c_cc[VTIME] = 0;
	ioctl(0, TIOCGWINSZ, &win);
	e->t.nb_col = win.ws_col;
	e->t.nb_row = win.ws_row;
	if (tcsetattr(0, 0, &(e->t.term)) == -1)
		return (0);
	return (1);
}

int			ft_reset_termios(t_env *e)
{
	if (tcsetattr(0, 0, &(e->t.bterm)) == -1)
		return (0);
	return (1);
}
