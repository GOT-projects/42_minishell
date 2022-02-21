#include "../../includes/mini_shell.h"

void	ft_tolower_str(char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
	{
		str[i] = ft_tolower(str[i]);
		++i;
	}
}

int	ft_prepare_cmd(t_shell *shell, t_operation *op)
{
	size_t	i;
	int		**var;

	i = 0;
	while (op->cmd[i])
	{
		var = ft_replace_var(shell, &(op->cmd[i]));
		op->cmd[i] = ft_remove_quote(shell, op->cmd[i], var);
		if (!(op->cmd[i]))
			return (1);
		if (!i)
			ft_tolower_str(op->cmd[0]);
		++i;
	}
	return (0);
}

int	ft_exec(t_shell *shell, t_operation *op)
{
	if (op->genre == CMD)
	{
		shell->last_exit_status = ft_prepare_cmd(shell, op);
		if (shell->last_exit_status)
			return (shell->last_exit_status);
		return (ft_exec_cmd(shell, op->cmd));
	}
	else if (op->genre == PIPE)
		return (ft_exec_pipe(shell, op));
	else if (op->genre == REDIRECTION)
	{
		shell->last_exit_status = ft_exec_redir(shell, op);
		return (shell->last_exit_status);
	}
	return (1);
}
