/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 17:02:13 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/11 19:10:04 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_client.h"

static void		ft_history_cmd_up(t_env *e, int fd)
{
	t_list			*lst;

	if (e->history && !e->h_pos)
	{
		lst = e->history;
		while (lst && lst->next)
			lst = lst->next;
		e->h_pos = lst;
		ft_terminos_clean_line(e);
		free(e->fds[fd].r_buffer);
		RB(fd) = ft_strdup((char*)e->h_pos->content);
		e->t.cur = ft_strlen(e->t.prompt) + ft_strlen(RB(fd));
		ft_client_prompt(e, e->t.cur);
		e->t.cur = ft_strlen(e->t.prompt) + ft_strlen(RB(fd));
	}
	else if (e->h_pos && e->h_pos->prev)
	{
		e->h_pos = e->h_pos->prev;
		free(e->fds[fd].r_buffer);
		ft_terminos_clean_line(e);
		RB(fd) = ft_strdup((char*)e->h_pos->content);
		e->t.cur = ft_strlen(e->t.prompt) + ft_strlen(RB(fd));
		ft_client_prompt(e, e->t.cur);
		e->t.cur = ft_strlen(e->t.prompt) + ft_strlen(RB(fd));
	}
}

static void		ft_history_cmd_down(t_env *e, int fd)
{
	if (e->h_pos && e->h_pos->next)
	{
		e->h_pos = e->h_pos->next;
		free(e->fds[fd].r_buffer);
		ft_terminos_clean_line(e);
		RB(fd) = ft_strdup((char*)e->h_pos->content);
		e->t.cur = ft_strlen(e->t.prompt) + ft_strlen(RB(fd));
		ft_client_prompt(e, e->t.cur);
		e->t.cur = ft_strlen(e->t.prompt) + ft_strlen(RB(fd));
	}
	else if (e->h_pos)
	{
		e->h_pos = NULL;
		free(e->fds[fd].r_buffer);
		ft_terminos_clean_line(e);
		RB(fd) = ft_strnew(0);
		e->t.cur = ft_strlen(e->t.prompt) + ft_strlen(RB(fd));
		ft_client_prompt(e, e->t.cur);
		e->t.cur = ft_strlen(e->t.prompt) + ft_strlen(RB(fd));
	}
}

void			ft_history_cmd(t_env *e, int fd, char c)
{
	if (c == ARROW_UP)
		ft_history_cmd_up(e, fd);
	else if (c == ARROW_DOWN)
		ft_history_cmd_down(e, fd);
}

void			ft_history_cmd_add(t_env *e, char *cmd)
{
	t_list		*lst;
	int			ocur;

	ocur = ft_strfocur(cmd, '\n');
	if (ocur >= 0)
		cmd[ocur] = '\0';
	if (ft_strlen(cmd) > 0)
	{
		lst = ft_lstnew(cmd, ft_strlen(cmd));
		if (!e->history)
			e->history = lst;
		else
			ft_lstaddend_free(&e->history, lst, u_del);
	}
	e->h_pos = NULL;
}

void			ft_history_cmd_clear(t_env *e)
{
	if (e->history)
	{
		ft_lstdel(&e->history, u_del);
		e->history = NULL;
	}
}