/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_replace_str.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 11:09:25 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/21 14:13:59 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char		*ft_str_replace_str(char *str, char *find, char *replace)
{
	int		i[3];
	char	*tmp;
	char	*tmp2;

	i[0] = (int)ft_strlen(find);
	i[1] = 0;
	i[2] = (int)ft_strlen(str);
	tmp2 = ft_strdup("");
	while (i[1] < (i[2] - i[0]) + 1)
	{
		tmp = ft_strsub(str, (unsigned int)i[1], (size_t)i[0]);
		if (ft_strcmp(tmp, find) == 0)
			tmp2 = ft_strjoin_free(tmp2, replace, 1);
		else
			tmp2 = ft_strjoin_free(tmp2, tmp, 1);
		free(tmp);
		i[1]++;
	}
	return (tmp2);
}
