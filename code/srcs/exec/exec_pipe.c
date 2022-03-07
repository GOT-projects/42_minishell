/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges <aartiges@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 20:08:25 by aartiges &        #+#    #+#             */
/*   Updated: 2022/03/07 17:38:56 by aartiges         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

/**
 * @brief allocation of the pids
 * 
 * @param nb_childs the number of the pids that will be create
 * @param pipes the pipes
 * @return pid_t* array of pids (not fork)
 */
static pid_t	*ft_get_pids(size_t nb_childs, int ***pipes)
{
	pid_t	*pids;

	if (*pipes)
	{
		pids = malloc(nb_childs * sizeof(pid_t));
		if (!pids)
		{
			ft_free_pipes(pipes, nb_childs + 1);
			return (NULL);
		}
		return (pids);
	}
	return (NULL);
}

/**
 * @brief allocation of the pipes
 * 
 * @param nb_pipes the number of pipes
 * @return int** the pipes
 */
static int	**ft_get_pipes(size_t nb_pipes)
{
	size_t	i;
	int		**pipes;

	pipes = malloc(nb_pipes * sizeof(int *));
	if (!pipes)
		return (NULL);
	ft_bzero(pipes, nb_pipes * sizeof(int *));
	i = 1;
	while (i < nb_pipes - 1)
	{
		pipes[i] = malloc(2 * sizeof(int));
		if (!pipes[i])
		{
			while (i > 0)
				free(pipes[--i]);
			free(pipes);
			return (NULL);
		}
		++i;
	}
	return (pipes);
}

/**
 * @brief the code of the child process
 * 
 * @param shell the shell
 * @param op the child node
 * @param pipes the pipes
 * @param i the number of the process
 */
static void	ft_exec_pipe_fork(t_shell *shell, t_node *op, int *pipes[2],
	size_t i)
{
	int	status;

	exec_mode_sub_process();
	if (pipes[i])
	{
		dup2(pipes[i][READ], READ);
		close(pipes[i][READ]);
		close(pipes[i][WRITE]);
	}
	if (pipes[i + 1])
	{
		dup2(pipes[i + 1][WRITE], WRITE);
		close(pipes[i + 1][WRITE]);
		close(pipes[i + 1][READ]);
	}
	status = ft_exec(shell, op);
	exit(status);
}

static size_t	ft_pipe_init(int ***pipes, pid_t **pids, t_node *op)
{
	size_t	nb_childs;

	nb_childs = ft_op_bro_size(op->childs);
	*pipes = ft_get_pipes(nb_childs + 1);
	*pids = ft_get_pids(nb_childs, pipes);
	return (nb_childs);
}

/**
 * @brief function that execute the pipe
 * 
 * @param shell the shell
 * @param op the node of the pipe
 * @return int 0 at success, else > 0
 */
int	ft_exec_pipe(t_shell *shell, t_node *op)
{
	size_t	i;
	size_t	nb_childs;
	int		**pipes;
	pid_t	*pids;

	nb_childs = ft_pipe_init(&pipes, &pids, op);
	if (!pipes || !pids)
		return (1);
	i = 0;
	op = op->childs;
	while (op)
	{
		if (i + 1 < nb_childs && pipe(pipes[i + 1]) == -1)
			return (ft_error_create_pipe(pids, i, &pipes, nb_childs));
		pids[i] = fork();
		if (pids[i] < 0)
			return (ft_error_fork_of_pipe(pids, i, &pipes, nb_childs));
		else if (pids[i] == 0)
			ft_exec_pipe_fork(shell, op, pipes, i);
		if (pipes[i])
			ft_close_pipe(pipes[i]);
		++i;
		op = op->next;
	}
	return (ft_end_of_pipe(shell, pids, &pipes, nb_childs));
}
