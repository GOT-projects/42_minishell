/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmilhas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 21:23:58 by jmilhas           #+#    #+#             */
/*   Updated: 2021/11/16 21:23:58 by jmilhas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_putnbr(int n)
{
	int	res;

	res = 0;
	if (n == 0)
		res += ft_putchar('0');
	if (n == -2147483648)
		res += ft_putstr("-2147483648");
	if (n < 0 && n != -2147483648)
	{
		res += ft_putchar('-');
		n = -n;
	}
	if (n <= 9 && n > 0)
		res += ft_putchar(n + 48);
	else if (n > 0)
	{
		res += ft_putnbr(n / 10);
		res += ft_putchar(n % 10 + 48);
	}
	return (res);
}
