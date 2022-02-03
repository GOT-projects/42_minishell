/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmilhas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 01:10:21 by jmilhas           #+#    #+#             */
/*   Updated: 2021/11/17 01:10:21 by jmilhas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_putnbr_unsigned(unsigned int n)
{
	int	res;

	res = 0;
	if (n == 0)
		res += ft_putchar('0');
	if (n <= 9 && n > 0)
		res += ft_putchar(n + 48);
	else if (n > 0)
	{
		res += ft_putnbr_unsigned(n / 10);
		res += ft_putchar(n % 10 + 48);
	}
	return (res);
}
