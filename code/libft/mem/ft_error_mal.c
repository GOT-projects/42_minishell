/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_mal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges <aartiges@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 18:12:31 by jmilhas           #+#    #+#             */
/*   Updated: 2022/02/08 02:00:31 by aartiges         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_error_mal(void *mem, t_track **track)
{
	if (!mem)
	{
		ft_putstr_fd("Error allocation\n..", 2);
		if ((*track)->len > 0)
			ft_track_free_all(track);
	}
	return (mem);
}

void	**ft_error_malt(void **mem, t_track **track)
{
	if (!mem)
	{
		ft_putstr_fd("Error allocation\n..", 2);
		if ((*track)->len > 0)
			ft_track_free_all(track);
	}
	return (mem);
}
