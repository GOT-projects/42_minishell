/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmilhas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 18:13:07 by jmilhas           #+#    #+#             */
/*   Updated: 2021/11/03 19:31:36 by jmilhas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int	ft_len_str(long long int n)
{
	long long int	i;

	i = 1;
	if (n < 0)
		n = n * -1;
	while (n >= 10)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static char	*ft_complet(char *str, long long int n, int len)
{
	int		debut;

	str[len] = '\0';
	len = len - 1;
	if (n < 0)
	{
		n = n * -1;
		debut = 1;
		str[0] = '-';
	}
	else
		debut = 0;
	while (len >= debut)
	{
		str[len] = n % 10 + '0';
		n = n / 10;
		len--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	long long int	lln;
	int				len;
	char			*str;

	lln = n;
	len = ft_len_str(lln);
	if (lln < 0)
		len = len + 1;
	str = (char *)ft_memalloc(len + 1);
	if (!str)
		return (NULL);
	str = ft_complet(str, lln, len);
	return (str);
}
