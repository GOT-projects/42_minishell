/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_unbase.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges <aartiges@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 01:05:03 by jmilhas           #+#    #+#             */
/*   Updated: 2022/02/04 20:39:23 by aartiges         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int	ft_sort_int_tab(char *str)
{
	size_t	i;
	size_t	m;

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

int	ft_putnbr_unbase(unsigned int nbr, char *base, int res)
{
	unsigned int	i;
	int				size;

	size = ft_strlen(base);
	i = 0;
	if (size <= 1)
		return (0);
	if (!ft_sort_int_tab(base))
		return (0);
	if (nbr / size)
	{
		ft_putnbr_base(nbr / size, base, res);
		res += ft_putchar(base[nbr % size]);
	}
	else
		res += ft_putchar(base[nbr % size]);
	return (res);
}
