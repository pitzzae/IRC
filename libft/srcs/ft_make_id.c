/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_id.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 13:14:54 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/15 13:17:08 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <sys/time.h>

unsigned long	ft_make_id(unsigned long u_id)
{
	struct timeval	t;
	unsigned long	id;

	gettimeofday(&t,NULL);
	id = (unsigned long)((t.tv_sec * 1000 * 1000) + (t.tv_usec * 1000)) << 24;
	id |= (u_id % 16777216) << 24;
	return id;
}
