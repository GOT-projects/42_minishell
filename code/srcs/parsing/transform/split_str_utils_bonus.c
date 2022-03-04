/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_str_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges <aartiges@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 23:13:22 by aartiges          #+#    #+#             */
/*   Updated: 2022/03/02 23:13:24 by aartiges         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mini_shell.h"

/**
 * @brief Create a string that are a substring
 * 
 * @param str the base string
 * @param start index of the start of the substring
 * @param end index of the end of the substring
 * @return ** char* the new string
 */
char	*create_string(char *str, size_t start, size_t end)
{
	size_t	i;
	char	*ret;

	ret = malloc(sizeof(char) * (end - start + 1));
	if (!ret)
		return (NULL);
	i = start;
	while (i < end)
	{
		ret[i - start] = str[i];
		i++;
	}
	ret[end - start] = '\0';
	return (ret);
}

/**
 * @brief free an array double dimensions
 * The 2nd dimension is free up to index
 * 
 * @param split the array 2 domensions
 * @param index the index of the 2nd dimension (last to be free)
 * @return ** int return always 1
 */
int	ft_free2d_index(char **split, size_t index)
{
	size_t	i;

	i = 0;
	while (i <= index)
		free(split[i]);
	free(split);
	return (1);
}
