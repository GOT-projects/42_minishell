#include "../../includes/mini_shell.h"

int	ft_exec(t_shell *shell, t_operation *op)
{
	if (op->genre == CMD)
		return (ft_exec_cmd(shell, op->cmd));
	if (op->genre == PIPE)
	{
		shell->last_exit_status = ft_exec_pipe(shell, op);
		return (shell->last_exit_status);
	}
	return (1);
}
