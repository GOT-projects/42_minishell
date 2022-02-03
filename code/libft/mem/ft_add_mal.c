/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_mal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmilhas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 18:12:31 by jmilhas           #+#    #+#             */
/*   Updated: 2021/11/03 18:48:52 by jmilhas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	**ft_add_malloc(t_track *track, int len)
{
	void	**dest;
	int		i;

	i = 0;
	if (len == 0)
		len = 1;
	if (track->len == 0)
	{
		dest = ft_error_mal((void **)malloc(sizeof(void *) * (len + 1)), track);
		ft_bzero(dest, sizeof(dest) * (len + 1));
		track->len += len + 1;
		return (dest);
	}
	dest = ft_error_mal(malloc(sizeof(void *) * (track->len + len)), track);
	ft_bzero(dest, sizeof(dest) * (track->len + len));
	while (track->mem[i] != NULL)
	{
		dest[i] = track->mem[i];
		i++;
	}
	track->len += len;
	free(track->mem);
	return (dest);
}

void	*ft_track(void *src, t_track *track)
{
	int	i;

	i = 0;
	ft_error_mal(src, track);
	track->mem = ft_add_malloc(track, 0);
	while (track->mem[i] != NULL)
		i++;
	track->mem[i] = src;
	return (src);
}

void	**ft_track_tab(void **src, t_track *track)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	ft_error_malt(src, track);
	while (src[len] != NULL)
		len++;
	track->mem = ft_add_malloc(track, len + 1);
	while (track->mem[i] != NULL)
		i++;
	len = 0;
	while (src[len] != NULL)
		track->mem[i++] = src[len++];
	track->mem[i] = src;
	return (src);
}
