#include "../../includes/mini_shell.h"

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

static int	ft_set_pipes(int **pipes, size_t nb_pipes)
{
	size_t	i;

	i = 1;
	while (i < nb_pipes - 1)
	{
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe");
			while (i > 1)
			{
				close(pipes[--i][READ]);
				close(pipes[i][WRITE]);
			}
			return (1);
		}
		++i;
	}
	return (0);
}

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
	if (ft_set_pipes(pipes, nb_pipes))
		ft_free_pipes(&pipes, nb_pipes);
	return (pipes);
}

static void	ft_exec_pipe_fork(t_shell *shell, t_operation *op, int *pipes[2],
	int i)
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

int	ft_exec_pipe(t_shell *shell, t_operation *op)
{
	size_t	i;
	size_t	nb_childs;
	int		**pipes;
	pid_t	*pids;

	nb_childs = ft_op_bro_size(op->childs);
	pipes = ft_get_pipes(nb_childs + 1);
	pids = ft_get_pids(nb_childs, &pipes);
	if (!pipes || !pids)
		return (1);
	i = 0;
	op = op->childs;
	while (op)
	{
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
