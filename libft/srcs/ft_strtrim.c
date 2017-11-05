/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 16:25:12 by gtorresa          #+#    #+#             */
/*   Updated: 2017/10/23 19:03:22 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static char		*clean_start_c(char const *s)
{
	size_t			i;

	i = 0;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	return (ft_strsub(s, (unsigned int)i, ft_strlen(s)));
}

static char		*clean_end_c(char const *s)
{
	size_t			i;

	i = ft_strlen(s) - 1;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i--;
	return (ft_strsub(s, 0, i + 1));
}

char			*ft_strtrim(char const *s)
{
	char			*str;

	str = clean_start_c(s);
	if (str == NULL)
		return (NULL);
	str = clean_end_c(str);
	if (str == NULL)
		return (NULL);
	return (str);
}
