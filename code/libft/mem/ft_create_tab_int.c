/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_tab_int.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmilhas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 18:12:34 by jmilhas           #+#    #+#             */
/*   Updated: 2021/11/03 18:48:14 by jmilhas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
 
size_t	**ft_create_tab_size_t(size_t nb_all, size_t size_all)
{
	size_t	**tab;
	size_t	i;

	i = 0;
	tab = (size_t **)malloc(sizeof(size_t *) * (nb_all + 1));
	if (!tab)
		return (NULL);
	while (i <= nb_all)
	{
		tab[i] = (size_t *)malloc(sizeof(size_t) * size_all);
		if (!tab[i])
			return (NULL);
		ft_bzero(tab[i], sizeof(int) * size_all);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
