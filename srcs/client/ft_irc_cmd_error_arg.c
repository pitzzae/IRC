/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc_cmd_error_arg.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <null>                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 01:16:52 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/12 01:59:14 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_client.h"

int		ft_irc_cmd_error_arg(t_env *e, char *cmd, char *help)
{
	char		*tmp;

	tmp = ft_strjoin("Wrong argument on: ", cmd);
	tmp = ft_strjoin_free(tmp, help, 1);
	ft_irc_print(e, tmp, ft_strlen(tmp), 0);
	free(tmp);
	return (1);
}