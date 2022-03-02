/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges <aartiges@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 19:28:37 by aartiges &        #+#    #+#             */
/*   Updated: 2022/03/02 02:17:52 by aartiges         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

/**
 * @brief built-in, print all the args in the
 * terminal
 * 
 * @param args 
 * @return ** int 
 */
int	ft_echo(char **args)
{
	_Bool	nl;
	size_t	i;

	nl = true;
	i = 0;
	while (args && args[i] && !ft_strcmp(args[i], "-n"))
	{
		nl = false;
		++i;
	}
	while (args && args[i])
	{
		if (i)
			ft_putchar_fd(' ', 1);
		ft_putstr_fd(args[i++], 1);
	}
	if (nl)
		ft_putstr_fd("\n", 1);
	return (EXIT_SUCCESS);
}
