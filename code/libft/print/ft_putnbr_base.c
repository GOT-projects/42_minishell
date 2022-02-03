/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmilhas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 23:14:15 by jmilhas           #+#    #+#             */
/*   Updated: 2021/11/16 23:14:15 by jmilhas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int	ft_sort_int_tab(char *str)
{
	int	i;
	int	m;

	i = 0;
	while (str[i])
	{
		m = i + 1;
		while (str[m])
		{
			if (str[i] == str[m])
				return (0);
			++m;
		}
		++i;
	}
	return (1);
}

int	ft_putnbr_base(int nbr, char *base, int res)
{
	unsigned int	i;
	unsigned int	lnbr;
	unsigned int	size;

	lnbr = nbr;
	size = ft_strlen(base);
	i = 0;
	if (size <= 1)
		return (0);
	if (!ft_sort_int_tab(base))
		return (0);
	if (lnbr < 0)
	{
		res += ft_putchar('-');
		lnbr *= -1;
	}
	if (lnbr / size)
	{
		ft_putnbr_base(lnbr / size, base, res);
		res += ft_putchar(base[lnbr % size]);
	}
	else
		res += ft_putchar(base[lnbr % size]);
	return (res);
}
