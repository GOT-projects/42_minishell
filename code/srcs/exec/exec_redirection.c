#include "../../includes/mini_shell.h"

static int	ft_save_stdin_stdout(int std[2])
{
	std[READ] = dup(READ);
	if (std[READ] == -1)
	{
		perror("redirection: dup stdin");
		return (1);
	}
	std[WRITE] = dup(WRITE);
	if (std[WRITE] == -1)
	{
		perror("redirection: dup stdout");
		close(std[READ]);
		return (1);
	}
	return (0);
}

static int	ft_restore_stdin_stdout(int std[2])
{
	if (dup2(std[READ], READ) == -1)
	{
		perror("redirection: dup2 stdin");
		return (1);
	}
	if (dup2(std[WRITE], WRITE) == -1)
	{
		perror("redirection: dup2 stdout");
		return (1);
	}
	return (0);
}

static int	ft_apply_redirections(t_operation *redir)
{
	while (redir)
	{
		if (redir->type_redirection == OUT_1
			|| redir->type_redirection == OUT_2)
		{
			if (ft_apply_output_redirection(redir))
				return (1);
		}
		else
		{
			if (ft_apply_input_redirection(redir))
				return (1);
		}
		redir = redir->next;
	}
	return (0);
}

int	ft_exec_redir(t_shell *shell, t_operation *op)
{
	int	std[2];

	if (ft_save_stdin_stdout(std))
		return (1);
	if (ft_apply_redirections(op->lst_redir))
		return (1);
	op = op->childs;
	while (op)
	{
		ft_exec(shell, op);
		op = op->next;
	}
	if (ft_restore_stdin_stdout(std))
		return (1);
	return (0);
}
