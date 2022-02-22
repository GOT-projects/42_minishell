#include "../../includes/mini_shell.h"

int	ft_exec_bool(t_shell *shell, t_node *op)
{
	op = op->childs;
	if (op)
	{
		shell->last_exit_status = ft_exec(shell, op);
		op = op->next;
		while (op)
		{
			if ((op->type_bool == AND && shell->last_exit_status == 0)
				|| (op->type_bool == OR && shell->last_exit_status != 0))
				shell->last_exit_status = ft_exec(shell, op);
			else
				return (shell->last_exit_status);
			op = op->next;
		}
		return (shell->last_exit_status);
	}
	shell->last_exit_status = 1;
	return (shell->last_exit_status);
}
