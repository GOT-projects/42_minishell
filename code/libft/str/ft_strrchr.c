/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmilhas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 18:12:09 by jmilhas           #+#    #+#             */
/*   Updated: 2021/11/03 18:25:22 by jmilhas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int	n;

	n = ft_strlen((char *)str);
	while (n >= 0)
	{
		if (str[n] == c)
			return ((char *)str + n);
		n--;
	}
	return (NULL);
}
