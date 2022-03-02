/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges <aartiges@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 19:29:44 by aartiges &        #+#    #+#             */
/*   Updated: 2022/03/02 22:45:26 by aartiges         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

/**
 * @brief check if a string is a number
 * 
 * @param str the string
 * @return _Bool true if it's a number, else false
 */
_Bool	ft_is_numeric_str(char *str)
{
	size_t	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		++i;
	while (str[i])
		if (!ft_isdigit(str[i++]))
			return (false);
	return (true);
}

/**
 * @brief free all the allocation of the minishel
 * 
 * @param shell the shell
 */
void	ft_free_minishell(t_shell *shell)
{
	if (shell)
	{
		ft_track_free_all(&(shell->t_pars));
		ft_track_free_all(&(shell->t_env));
	}
}

/**
 * @brief function thatexit the current process with the status given
 * 
 * @param shell if set, the function will free the environnement of the
 * minishell
 * @param status exit code of the process
 * @return ** int if a problem occurs an error is return
 */
int	ft_exit(t_shell *shell, char **status)
{
	size_t	size;
	int		ret;

	size = 0;
	while (status[size])
		++size;
	status[0] = ft_track(ft_strtrim(status[0], SPACES), &(shell->t_pars));
	if (size > 0 && !ft_is_numeric_str(status[0]))
	{
		ft_putstr_fd("error\nexit: numeric argument required\n", 2);
		ft_free_minishell(shell);
		exit(255);
	}
	if (size > 1)
	{
		ft_putstr_fd("error\nexit: too many arguments\n", 2);
		shell->last_exit_status = 1;
		return (1);
	}
	ft_putstr_fd("exit\n", 1);
	ret = shell->last_exit_status;
	if (status[0])
		ret = ft_atoi(status[0]);
	ft_free_minishell(shell);
	exit(ret);
}
