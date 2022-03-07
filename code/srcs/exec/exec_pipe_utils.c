/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges <aartiges@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 20:01:19 by aartiges &        #+#    #+#             */
/*   Updated: 2022/03/07 17:34:33 by aartiges         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

/**
 * @brief free all pipes
 * 
 * @param pipes pipes
 * @param nb_pipes the number of pipes
 */
void	ft_free_pipes(int ***pipes, size_t nb_pipes)
{
	size_t	i;

	i = 0;
	while (i < nb_pipes)
		free((*pipes)[i++]);
	free((*pipes));
	pipes = NULL;
}

/**
 * @brief free all the pipes, take the return status of the last command pipe
 * and wait all the commands pipe
 * 
 * @param shell the shell
 * @param pids the process ids
 * @param pipes the pipes
 * @param nb_childs the number of commands pipe
 * @return int 0 at success, else > 0
 */
int	ft_end_of_pipe(t_shell *shell, pid_t *pids, int ***pipes, size_t nb_childs)
{
	int		status;
	size_t	i;

	i = 0;
	while (i < nb_childs - 1)
		waitpid(pids[i++], NULL, 0);
	waitpid(pids[i], &status, 0);
	ft_free_pipes(pipes, nb_childs + 1);
	free(pids);
	shell->last_exit_status = ft_error_exit_process("pipe", status);
	return (shell->last_exit_status);
}

/**
 * @brief code in case of error at fork
 * 
 * @param pids the process ids
 * @param i the number of the current fork that fail
 * @param pipes the pipes
 * @param nb_childs the number of commands pipe
 * @return int 1 allways
 */
int	ft_error_fork_of_pipe(pid_t *pids, size_t i, int ***pipes, size_t nb_childs)
{
	perror("fork of pipe");
	if ((*pipes)[i])
	{
		close((*pipes)[i][READ]);
		close((*pipes)[i][WRITE]);
	}
	if ((*pipes)[i + 1])
	{
		close((*pipes)[i + 1][READ]);
		close((*pipes)[i + 1][WRITE]);
	}
	while (i > 0)
	{
		kill(pids[--i], SIGKILL);
		wait(NULL);
	}
	ft_free_pipes(pipes, nb_childs + 1);
	free(pids);
	return (1);
}

int	ft_error_create_pipe(pid_t *pids, size_t i, int ***pipes, size_t nb_childs)
{
	perror("pipe");
	if ((*pipes)[i])
	{
		close((*pipes)[i][READ]);
		close((*pipes)[i][WRITE]);
	}
	while (i > 0)
	{
		kill(pids[--i], SIGKILL);
		wait(NULL);
	}
	ft_free_pipes(pipes, nb_childs + 1);
	free(pids);
	return (1);
}
