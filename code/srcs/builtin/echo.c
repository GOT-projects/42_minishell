/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges & jmilhas <x@student.42lyon.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 19:28:37 by aartiges &        #+#    #+#             */
/*   Updated: 2022/03/07 00:14:51 by aartiges &       ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

static int	ft_echo_flag_nl(char *arg)
{
	size_t	i;

	i = 0;
	while (arg[i])
	{
		if (!i && arg[i] != '-')
			return (0);
		if (i && arg[i] != 'n')
			return (0);
		++i;
	}
	if (i < 2)
		return (0);
	return (1);
}

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
	size_t	start;

	nl = true;
	i = 0;
	while (args && args[i] && ft_echo_flag_nl(args[i]))
	{
		nl = false;
		++i;
	}
	start = i;
	while (args && args[i])
	{
		if (i != start)
			ft_putchar_fd(' ', 1);
		ft_putstr_fd(args[i++], 1);
	}
	if (nl)
		ft_putstr_fd("\n", 1);
	return (EXIT_SUCCESS);
}
