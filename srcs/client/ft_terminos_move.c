/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_terminos_move.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 13:31:14 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/11 18:02:56 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_client.h"

void		ft_terminos_clean_line(t_env *e)
{
	int			cur;

	tputs(tgetstr("cb", NULL), 1, ft_myputchar);
	tputs(tgetstr("ce", NULL), 1, ft_myputchar);
	cur = e->t.cur;
	while (cur > 0)
	{
		tputs(tgetstr("le", NULL), 1, ft_myputchar);
		cur--;
	}
}

void		ft_terminos_add_char(t_env *e, int fd, char c)
{
	size_t			len;

	if (c == '\n')
		RB(fd) = ft_addchar_intstr(RB(fd), c, ft_strlen(RB(fd)));
	else
		RB(fd) = ft_addchar_intstr(RB(fd), c, e->t.cur - e->t.p_len);
	dprintf(7, "[u] e->t.cur %d e->t.p_len %d res: %d buff_len: %zu str: %s\n", e->t.cur, e->t.p_len, e->t.cur - e->t.p_len, ft_strlen(RB(fd)), RB(fd));
	if (ft_strlen(RB(fd)) + e->t.p_len == e->t.cur + 1)
		ft_putchar(c);
	else
	{
		len = ft_strlen(&RB(fd)[e->t.cur - e->t.p_len]) - 1;
		ft_putstr(&RB(fd)[e->t.cur - e->t.p_len]);
		while (len)
		{
			tputs(tgetstr("le", NULL), 1, ft_myputchar);
			len--;
		}
	}
	e->t.cur++;
}

void		ft_terminos_del_char(t_env *e, int fd)
{
	ft_terminos_clean_line(e);
	dprintf(7, "[j] e->t.cur %d e->t.p_len %d res: %d buff_len: %zu str: %s\n", e->t.cur, e->t.p_len, e->t.cur - e->t.p_len, ft_strlen(RB(fd)), RB(fd));
	RB(fd) = ft_delchar_intstr(RB(fd), e->t.cur - e->t.p_len - 1);
	dprintf(7, "[k] e->t.cur %d e->t.p_len %d res: %d buff_len: %zu str: %s\n", e->t.cur, e->t.p_len, e->t.cur - e->t.p_len, ft_strlen(RB(fd)), RB(fd));
	e->t.cur--;
	ft_client_prompt(e, e->t.cur - e->t.p_len);
	dprintf(7, "[l] e->t.cur %d e->t.p_len %d res: %d buff_len: %zu str: %s\n", e->t.cur, e->t.p_len, e->t.cur - e->t.p_len, ft_strlen(RB(fd)), RB(fd));
}

void		ft_terminos_left_arrow(t_env *e, int fd)
{
	if (e->t.cur > e->t.p_len)
	{
		tputs(tgetstr("le", NULL), 1, ft_myputchar);
		e->t.cur--;
	}
	(void)fd;
}

void		ft_terminos_right_arrow(t_env *e, int fd)
{
	if (e->t.cur < ft_strlen(RB(fd)) + e->t.p_len)
	{
		tputs(tgetstr("nd", NULL), 1, ft_myputchar);
		e->t.cur++;
	}
}