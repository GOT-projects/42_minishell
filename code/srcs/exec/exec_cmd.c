/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges <aartiges@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 19:41:01 by aartiges &        #+#    #+#             */
/*   Updated: 2022/03/03 23:32:15 by aartiges         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

/**
 * @brief execute a command (update the last exit status)
 * 
 * @param shell the shell
 * @param cmd arguments array of the command (like "ls" "-l" "/")
 * @return int -- the exit status
 */
int	ft_exec_cmd(t_shell *shell, char **cmd)
{
	errno = 0;
	if (!cmd[0])
	{
		ft_putstr_fd("No command found!!! This musn't to be\n", 2);
		shell->last_exit_status = ERR_404_EXEC;
	}
	else if (!ft_strcmp("exit", cmd[0]))
		shell->last_exit_status = ft_exit(shell, &(cmd[1]));
	else if (!ft_strcmp("cd", cmd[0]))
		shell->last_exit_status = ft_cd(shell, &(cmd[1]));
	else if (!ft_strcmp("pwd", cmd[0]))
		shell->last_exit_status = ft_pwd();
	else if (!ft_strcmp("export", cmd[0]))
		shell->last_exit_status = ft_export(shell, &(cmd)[1]);
	else if (!ft_strcmp("env", cmd[0]))
		shell->last_exit_status = ft_env(shell);
	else if (!ft_strcmp("unset", cmd[0]))
		shell->last_exit_status = ft_unset(shell, &(cmd[1]));
	else if (!ft_strcmp("echo", cmd[0]))
		shell->last_exit_status = ft_echo(&(cmd[1]));
	else
		shell->last_exit_status = ft_exec_prg(shell, cmd);
	return (shell->last_exit_status);
}
