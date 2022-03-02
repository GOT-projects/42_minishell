/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges <aartiges@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 22:59:23 by aartiges          #+#    #+#             */
/*   Updated: 2022/03/02 22:59:25 by aartiges         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

/**
 * @brief check if a string start with the string that we want
 * 
 * @param str the string that will be check
 * @param to_find the string that we want at the start
 * @return _Bool true if str start with to_find, else false
 */
_Bool	ft_str_start_with(char *str, char *to_find)
{
	size_t	j;

	j = 0;
	while (str[j] && to_find[j] && str[j] == to_find[j])
		++j;
	if (to_find[j] == 0)
		return (true);
	return (false);
}

/**
 * @brief /!\ function with side effect /!\ change the state of the quotes
 * That is use when we do a character string traversal
 * 
 * @param c the current character of the string
 * @param quote a pointer on the state of the quote (when quote = 0
 * the character is not into quotes)
 * @return int 0 if the state has not change
 */
int	ft_pars_quote(char c, char *quote)
{
	if (!(*quote) && (c == '"' || c == '\''))
	{
		(*quote) = c;
		return (1);
	}
	else if ((*quote) == c)
	{
		(*quote) = 0;
		return (1);
	}
	return (0);
}

int	ft_pars_parenthese(char c, int *parenthese)
{
	if (c == '(')
	{
		++(*parenthese);
		return (1);
	}
	if (c == ')')
	{
		--(*parenthese);
		return (1);
	}
	return (0);
}

/**
 * @brief free an array with double dimensions
 * 
 * @param array the array that will be free
 */
void	ft_free_2d(char **array)
{
	size_t	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}
