#include "../../includes/mini_shell.h"

int	ft_exec_sub_shell(t_shell *shell, t_node *op)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		shell->last_exit_status = 1;
		return (shell->last_exit_status);
	}
	if (pid == 0)
		exit(ft_exec(shell, op->childs));
	waitpid(pid, &status, 0);
	shell->last_exit_status = ft_error_exit_process("sub_shell", status);
	return (shell->last_exit_status);
}
