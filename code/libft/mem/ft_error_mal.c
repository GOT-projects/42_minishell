/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_mal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmilhas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 18:12:31 by jmilhas           #+#    #+#             */
/*   Updated: 2021/11/03 18:48:52 by jmilhas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_error_mal(void *mem, t_track *track)
{
	if (!mem)
	{
		ft_putstr_fd("Error allocation\n..", 2);
		if (track->len > 0)
			ft_track_free_all(track);
		exit (EXIT_FAILURE);
	}
	return (mem);
}

void	**ft_error_malt(void **mem, t_track *track)
{
	if (!mem)
	{
		ft_putstr_fd("Error allocation\n..", 2);
		if (track->len > 0)
			ft_track_free_all(track);
		exit (EXIT_FAILURE);
	}
	return (mem);
}
