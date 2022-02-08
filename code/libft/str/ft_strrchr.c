/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges <aartiges@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 18:12:09 by jmilhas           #+#    #+#             */
/*   Updated: 2022/02/04 20:23:43 by aartiges         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strrchr(const char *str, int c)
{
	size_t	n;

	n = ft_strlen((char *)str);
	while (n > 0)
	{
		if (str[n] == c)
			return ((char *)str + n);
		n--;
	}
	if (str[n] == c)
		return ((char *)str + n);
	return (NULL);
}
