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

int	ft_error_fork_of_pipe(pid_t *pids, size_t i, int ***pipes, size_t nb_childs)
{
	perror("fork of pipe");
	while (i > 0)
		kill(pids[--i], SIGKILL);
	ft_free_pipes(pipes, nb_childs + 1);
	free(pids);
	return (1);
}
