/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmilhas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 18:12:02 by jmilhas           #+#    #+#             */
/*   Updated: 2021/11/03 21:47:00 by jmilhas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strnstr(const char *str, const char *to_found, size_t n)
{
	size_t	i;
	size_t	j;
	char	*pt;

	i = 0;
	pt = 0;
	if (to_found[i] == '\0')
		return ((char *)str);
	while (str[i] != '\0' && i < n)
	{
		if (str[i] == to_found[0])
		{
			pt = (char *)str + i;
			j = 0;
			while (str[i + j] == to_found[j] && i + j < n)
			{
				if (to_found[j + 1] == '\0')
					return (pt);
				j++;
			}
			pt = 0;
		}
		i++;
	}
	return (NULL);
}
