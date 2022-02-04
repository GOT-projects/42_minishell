/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges <aartiges@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 21:04:25 by jmilhas           #+#    #+#             */
/*   Updated: 2022/02/04 20:33:50 by aartiges         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_putstr(char *str)
{
	size_t	res;

	if (!str)
		return (0);
	res = 0;
	while (*str)
	{
		res += ft_putchar(*str);
		str++;
	}
	return (res);
}
