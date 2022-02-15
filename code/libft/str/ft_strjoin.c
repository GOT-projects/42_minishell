/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges <aartiges@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 18:58:58 by jmilhas           #+#    #+#             */
/*   Updated: 2022/02/04 20:25:18 by aartiges         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_joint(char *dest, char const *s2, size_t i, char *tmp)
{
	size_t	len;
	size_t	j;

	len = ft_strlen(tmp);
	j = 0;
	while (j < len)
	{
		dest[i] = tmp[j];
		j++;
		i++;
	}
	if (tmp == s2)
		return (dest);
	return (ft_joint(dest, s2, i, (char *)s2));
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	size;
	char	*str;
	size_t	i;

	size = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)ft_memalloc(size + 1);
	if (!str)
		return (NULL);
	i = 0;
	ft_joint(str, s2, i, (char *)s1);
	return (str);
}
