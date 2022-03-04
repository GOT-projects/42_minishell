/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_tab_int.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges <aartiges@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 18:12:34 by jmilhas           #+#    #+#             */
/*   Updated: 2022/03/02 23:09:47 by aartiges         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	**ft_create_tab_int(int nb_all, int size_all)
{
	int	**tab;
	int	i;

	i = 0;
	tab = (int **)malloc(sizeof(int *) * (nb_all + 1));
	if (!tab)
		return (NULL);
	while (i < nb_all)
	{
		tab[i] = (int *)ft_memalloc(sizeof(int) * (size_all + 1));
		if (!tab[i])
			return (NULL);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
