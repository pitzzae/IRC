/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_cmd_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 19:53:45 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/11 21:51:58 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_client.h"

int			ft_irc_cmd_file(t_env *e, int cs)
{
	char			*tmp;

	if (BL(cs) > 5 && ft_strncmp(RB(cs), "/file", 5) == 0)
	{
		tmp = "• /file not implemented yet\n";
		ft_irc_print(e, tmp, ft_strlen(tmp), 0);
		ft_history_cmd_add(e, RB(cs));
		return (1);
	}
	return (0);
}
