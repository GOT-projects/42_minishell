#include "../../includes/mini_shell.h"

void	ft_free_pipes(int ***pipes, size_t nb_pipes)
{
	size_t	i;

	i = 0;
	while (i < nb_pipes)
		free((*pipes)[i++]);
	free((*pipes));
	pipes = NULL;
}

int	ft_set_pipes(int **pipes, size_t nb_pipes)
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

int	**ft_get_pipes(size_t nb_pipes)
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

int	ft_exec_pipe(t_shell *shell, t_operation *op)
{
	size_t	i;
	size_t	nb_childs;
	int		**pipes;
	pid_t	*pids;
	int		status;

	nb_childs = ft_op_bro_size(op->childs);
	pipes = ft_get_pipes(nb_childs + 1);
	if (!pipes)
		return (1);
	pids = malloc(nb_childs * sizeof(pid_t));
	if (!pids)
	{
		ft_free_pipes(&pipes, nb_childs + 1);
		return (1);
	}
	i = 0;
	op = op->childs;
	while (op)
	{
		pids[i] = fork();
		if (pids[i] < 0)
		{
			perror("fork of pipe");
			while (i > 0)
				kill(pids[--i], SIGKILL);
			ft_free_pipes(&pipes, nb_childs + 1);
			free(pids);
			return (1);
		}
		else if (pids[i] == 0)
		{
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
		if (pipes[i])
		{
			close(pipes[i][READ]);
			close(pipes[i][WRITE]);
		}
		++i;
		op = op->next;
	}
	i = 0;
	while (i < nb_childs - 1)
		waitpid(pids[i++], &status, 0);
	waitpid(pids[i], &status, 0);
	ft_free_pipes(&pipes, nb_childs + 1);
	free(pids);
	return (ft_error_exit_process("pipe", status));
}
