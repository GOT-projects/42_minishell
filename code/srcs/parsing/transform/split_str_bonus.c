/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_str_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges <aartiges@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 23:13:05 by aartiges          #+#    #+#             */
/*   Updated: 2022/03/02 23:13:07 by aartiges         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mini_shell.h"

static size_t	ft_nbsplit(char *s, char *to_find, size_t len_to_find, int p)
{
	size_t	i;
	size_t	count;
	size_t	start;
	char	quote;

	i = 0;
	start = 0;
	count = 0;
	quote = 0;
	while (s[i])
	{
		if (!ft_pars_quote(s[i], &quote) && !quote
			&& !ft_pars_parenthese(s[i], &p) && p == 0)
		{
			if (!quote && ft_str_start_with(s + i, to_find) && i > start)
				count++;
			if (!quote && ft_str_start_with(s + i, to_find))
				start = i + len_to_find;
		}
		i++;
	}
	if (s[start] != 0)
		count++;
	return (count);
}

static int	ft_split_str_finalise(char **split, char *str, size_t index[2],
	int start)
{
	if (index[0] == 0)
		split[index[1]] = NULL;
	if (str[start] != 0)
	{
		split[(index[1])++] = create_string(str, start, index[0]);
		if (!split[index[1] - 1])
			return (!ft_free2d_index(split, index[1] - 2));
	}
	return (1);
}

static int	write_split(char **split, char *str, char *to_find,
	size_t len_to_find)
{
	size_t	index[3];
	char	quote;
	int		p;

	ft_bzero(index, 3 * sizeof(char *));
	quote = 0;
	p = 0;
	while (str[index[0]])
	{
		if (!ft_pars_quote(str[index[0]], &quote) && !quote
			&& !ft_pars_parenthese(str[index[0]], &p) && p == 0)
		{
			if (!quote && ft_str_start_with(str + index[0], to_find)
				&& index[0] > index[2])
			{
				split[(index[1])++] = create_string(str, index[2], index[0]);
				if (!split[index[1] - 1])
					return (!ft_free2d_index(split, index[1] - 2));
			}
			if (!quote && ft_str_start_with(str + index[0], to_find))
				index[2] = index[0] + len_to_find;
		}
		(index[0])++;
	}
	return (ft_split_str_finalise(split, str, index, index[2]));
}

/**
 * @brief split a string taking into account the quotes
 * 
 * @param s the string to split
 * @param to_find the separator's string
 * @return char** the split of s by to_find or NULL if error
 */
char	**ft_split_str(char const *s, char *to_find)
{
	char	**split;
	size_t	size;
	size_t	len_to_find;

	if (!s)
		return (NULL);
	len_to_find = ft_strlen(to_find);
	size = ft_nbsplit((char *)s, to_find, len_to_find, 0);
	split = malloc((size + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	split[size] = NULL;
	if (write_split(split, (char *)s, to_find, len_to_find))
		return (split);
	return (NULL);
}
