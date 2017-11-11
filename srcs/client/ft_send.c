/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_send.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 21:32:33 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/11 21:32:33 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc_client.h"

size_t			ft_send(int cs, void *buff, size_t len, t_env *e)
{
	int		r;

	(void)e;
	r = send(cs, buff, len, 0);
	return (r);
}