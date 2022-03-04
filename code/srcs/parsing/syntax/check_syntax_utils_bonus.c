/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_utils_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges <aartiges@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 23:06:08 by aartiges          #+#    #+#             */
/*   Updated: 2022/03/02 23:06:09 by aartiges         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mini_shell.h"

/**
 * @brief check if all parentheses open are close
 * 
 * @param line the command line
 * @return _Bool true if ok, false else
 */
_Bool	ft_check_parenthese_post_pars(char *line)
{
	size_t	i;
	char	quote;
	int		tmp;

	tmp = 0;
	quote = 0;
	i = 0;
	while (line[i] && tmp >= 0)
	{
		if (!ft_pars_quote(line[i], &quote) && !quote)
		{
			if (line[i] == '(')
				++tmp;
			else if (line[i] == ')')
				--tmp;
		}
		if (tmp < 0)
			return (false);
		++i;
	}
	if (!quote && tmp == 0)
		return (true);
	return (false);
}
