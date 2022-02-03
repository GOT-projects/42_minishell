/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmilhas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 18:13:36 by jmilhas           #+#    #+#             */
/*   Updated: 2021/11/03 18:13:37 by jmilhas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strndup(const char *s, size_t size)
{
	char	*res;

	res = malloc(sizeof(char) * (size + 1));
	if (!res)
		return (0);
	ft_memcpy(res, s, size);
	res[size] = 0;
	return (res);
}
