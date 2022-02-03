/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdupcat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmilhas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 18:07:17 by jmilhas           #+#    #+#             */
/*   Updated: 2021/12/17 18:07:17 by jmilhas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include ".././include/libft.h"

char	*ft_strdupcat(char *dest, const char *src)
{
	char	*str;
	int		i;
	int		j;

	str = NULL;
	str = (char *)ft_memalloc(ft_strlen(dest) + ft_strlen(src) + 1);
	i = 0;
	j = 0;
	while (dest[i])
	{
		str[j] = dest[i];
		i++;
		j++;
	}
	i = 0;
	while (src[i])
	{
		str[j] = src[i];
		i++;
		j++;
	}
	free(dest);
	free((char *)src);
	return (str);
}
