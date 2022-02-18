#include "../../includes/mini_shell.h"

int	ft_apply_output_redirection(t_operation *redir)
{
	int	fd;

	if (redir->type_redirection == OUT_1)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror("open error");
		return (1);
	}
	if (dup2(fd, 1) == -1)
	{
		perror("redirection: output file: redirection");
		return (1);
	}
	return (0);
}
/*
int	ft_apply_input_redirection(t_operation *redir)
{

	return (0);
}
*/