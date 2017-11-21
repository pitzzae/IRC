/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_update_prompt.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 02:39:46 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/21 14:13:56 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_client.h"

void			ft_irc_update_prompt(t_env *e)
{
	char		*new_p;

	if (e->nick || e->host || e->chan)
	{
		new_p = ft_strnew(0);
		if (e->nick)
			new_p = ft_strjoin_free(new_p, e->nick, 1);
		if (e->host)
		{
			new_p = ft_strjoin_free(new_p, "@", 1);
			new_p = ft_strjoin_free(new_p, e->host, 1);
		}
		if (e->chan)
		{
			new_p = ft_strjoin_free(new_p, " ", 1);
			new_p = ft_strjoin_free(new_p, e->chan, 1);
		}
		new_p = ft_strjoin_free(new_p, "$>", 1);
		free(e->t.prompt);
		e->t.prompt = new_p;
		e->t.p_len = ft_strlen(e->t.prompt);
	}
}
