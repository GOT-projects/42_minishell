/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dec_to_bin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmilhas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 18:30:54 by jmilhas           #+#    #+#             */
/*   Updated: 2021/12/23 18:30:54 by jmilhas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	*ft_dec_to_bin(int nbr, int size)
{
	int	*binary;

	binary = (int *)malloc(sizeof(int) * size);
	if (!binary)
		return (NULL);
	while (nbr > 0)
	{
		size--;
		binary[size] = nbr % 2;
		nbr /= 2;
	}
	while (size > 0)
	{
		size--;
		binary[size] = 0;
	}
	return (binary);
}
