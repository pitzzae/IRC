/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_irc_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 15:44:59 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/07 19:07:34 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_irc.h"

int			ft_parse_irc_cmd(t_env *e, int cs)
{
	if (ft_irc_cmd_nick(e, cs))
		return (0);
	if (ft_irc_cmd_user(e, cs))
		return (0);
	if (ft_irc_cmd_who(e, cs))
		return (0);
	return (1);
}