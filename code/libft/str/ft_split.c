/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges <aartiges@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 18:58:09 by jmilhas           #+#    #+#             */
/*   Updated: 2022/02/04 20:25:18 by aartiges         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static size_t	split_len(const char *str, char c)
{
	size_t	i;
	size_t	trigger;

	i = 0;
	trigger = 0;
	while (*str)
	{
		if (*str != c && trigger == 0)
		{
			trigger = 1;
			i++;
		}
		else if (*str == c)
			trigger = 0;
		str++;
	}
	return (i);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	tmp;
	char	**split;

	if (!s)
		return (0);
	split = ft_calloc((split_len(s, c) + 1), sizeof(char *));
	if (!split)
		return (0);
	j = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		tmp = i;
		while (s[i] && s[i] != c)
			i++;
		if (i != tmp)
			split[j++] = ft_strndup(&s[tmp], i - tmp);
	}
	return (split);
}
