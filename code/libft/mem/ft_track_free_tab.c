/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_track_free_tab.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges <aartiges@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 18:12:31 by jmilhas           #+#    #+#             */
/*   Updated: 2022/02/08 03:07:43 by aartiges         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int	ft_check_track(t_track **track, void **mem, int *check, int *size)
{	
	*check = 0;
	*size = 0;
	while ((*track)->mem[*check] != mem[0])
		(*check)++;
	while (mem[*size] != NULL)
		(*size)++;
	(*size)++;
	return (0);
}

static void	**ft_tmp_free(t_track **track, void **dest, int size)
{
	dest = ft_error_mal(malloc(sizeof(void *) * ((*track)->len - size)), track);
	ft_bzero(dest, sizeof(dest) * ((*track)->len - size));
	(*track)->len -= size;
	return (dest);
}

void	**ft_track_free_tab(t_track **track, void **mem)
{
	void	**dest;
	int		var[3];
	int		check;
	int		size;

	dest = NULL;
	ft_bzero(var, sizeof(int) * 3);
	if (ft_check_track(track, mem, &check, &size) == -1)
		return (NULL);
	dest = ft_tmp_free(track, dest, size);
	while ((*track)->mem[var[0]] != NULL)
	{
		if (var[0] == check)
			while (var[2]++ < size)
				var[0]++;
		else
			dest[var[1]++] = (*track)->mem[var[0]++];
	}
	while (size-- > 0)
		free((*track)->mem[check++]);
	free((*track)->mem);
	(*track)->mem = dest;
	return (NULL);
}
