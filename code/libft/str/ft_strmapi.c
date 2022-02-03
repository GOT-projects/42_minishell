/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmilhas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 19:35:10 by jmilhas           #+#    #+#             */
/*   Updated: 2021/11/05 18:38:55 by jmilhas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	len;
	unsigned int	i;
	unsigned char	*tmp;

	if (!s || !f)
		return (NULL);
	i = 0;
	len = ft_strlen(s);
	tmp = (unsigned char *)ft_calloc(sizeof(char), len + 1);
	if (!tmp)
		return (NULL);
	while (i < len)
	{
		tmp[i] = f(i, s[i]);
		i++;
	}
	return ((char *)tmp);
}
