#include "../../includes/mini_shell.h"

int	ft_exec(t_shell *shell, t_operation *op)
{
	if (op->genre == CMD)
		return (ft_exec_cmd(shell, op->cmd));
	// add *
	return (1);
}
