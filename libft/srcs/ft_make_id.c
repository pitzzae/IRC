/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_id.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 13:14:54 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/18 15:24:38 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <sys/time.h>

unsigned long	ft_make_id(void)
{
	struct timeval	t;
	unsigned long	id;

	gettimeofday(&t, NULL);
	id = (unsigned long)((t.tv_usec) + (t.tv_usec * 100000000000)) << 24;
	id += t.tv_sec * 1000;
	return (id);
}
