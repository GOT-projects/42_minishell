/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges & jmilhas <x@student.42lyon.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 19:56:01 by aartiges &        #+#    #+#             */
/*   Updated: 2022/03/08 00:11:35 by aartiges &       ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

/**
 * @brief convert a string in a lower case string
 * 
 * @param str the string to convert
 */
void	ft_tolower_str(char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
	{
		str[i] = ft_tolower(str[i]);
		++i;
	}
}

/**
 * @brief prepare the command
 * 
 * @param shell the shell
 * @param op the node of the command
 * @return int 0 at success, else > 0
 */
int	ft_prepare_cmd(t_shell *shell, t_node *op)
{
	size_t	i;
	int		**var;
	int		*wd;

	i = 0;
	wd = ft_checker_wildcard(shell, op->cmd);
	while (op->cmd[i])
	{
		var = ft_replace_var(shell, &(op->cmd[i]));
		if (op->cmd[i][0] != '\0')
			op->cmd[i] = ft_remove_quote(shell, op->cmd[i], var);
		else
		{
			op->cmd = ft_remove_empty_cmd(op->cmd, i);
			i--;
		}
		if (!(op->cmd[i]))
			return (1);
		if (!i && !ft_strchr(op->cmd[0], '/'))
			ft_tolower_str(op->cmd[0]);
		++i;
	}
	op->cmd = ft_wildcard(shell, op->cmd, wd);
	return (0);
}

/**
 * @brief generic function to execute a node of the tree
 * 
 * @param shell the shell
 * @param op the node
 * @return int 0 if success, else the code error of the command or shell
 * manipulation
 */
int	ft_exec(t_shell *shell, t_node *op)
{
	if (op->genre == CMD)
	{
		shell->last_exit_status = ft_prepare_cmd(shell, op);
		if (shell->last_exit_status)
			return (shell->last_exit_status);
		return (ft_exec_cmd(shell, op->cmd));
	}
	else if (op->genre == PIPE)
	{
		shell->last_exit_status = ft_exec_pipe(shell, op);
		return (shell->last_exit_status);
	}
	else if (op->genre == REDIRECTION)
	{
		shell->last_exit_status = ft_exec_redir(shell, op);
		return (shell->last_exit_status);
	}
	else if (op->genre == BOOL)
		return (ft_exec_bool(shell, op));
	else if (op->genre == SUB_SHELL)
		return (ft_exec_sub_shell(shell, op));
	return (1);
}
