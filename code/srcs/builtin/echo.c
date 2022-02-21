/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges & jmilhas <x@student.42lyon.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 19:28:37 by aartiges &        #+#    #+#             */
/*   Updated: 2022/02/21 19:28:38 by aartiges &       ###   ########lyon.fr   */
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

	i = 0;
	nl = true;
	while (args && args[i])
	{
		if (i == MY_SIZE_T_MAX)
		{
			ft_putstr_fd("echo: too many arguments\n", 2);
			return (EXIT_FAILURE);
		}
		++i;
	}
	i = 0;
	while (args && args[i] && !ft_strcmp(args[i], "-n"))
	{
		nl = false;
		++i;
	}
	while (args && args[i])
		ft_putstr_fd(args[i++], 1);
	if (nl)
		ft_putstr_fd("\n", 1);
	return (EXIT_SUCCESS);
}
