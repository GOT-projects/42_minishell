#include "../includes/mini_shell.h"

void	debug_tree(t_operation *op, int level)
{
	int			i;
	int			j;
	t_operation	*redir;

	while (op)
	{
		i = 0;
		while (i++ < level)
			printf("\t");
		if (op->genre == PIPE)
		{
			printf("+PIPE\n");
			debug_tree(op->childs, level + 1);
		}
		else if (op->genre == REDIRECTION)
		{
			printf("+REDIRECTION\n");
			redir = op->lst_redir;
			while (redir)
			{
				i = 0;
				while (i++ < level + 1)
					printf("\t");
				if (redir->type_redirection == IN_1)
					printf("< %s\n", redir->file);
				else if (redir->type_redirection == IN_2)
					printf("<< %s\n", redir->file);
				else if (redir->type_redirection == OUT_1)
					printf("> %s\n", redir->file);
				else if (redir->type_redirection == OUT_2)
					printf(">> %s\n", redir->file);
				redir = redir->next;
			}
			debug_tree(op->childs, level + 2);
		}
		else if (op->genre == CMD)
		{
			printf("+CMD\n");
			j = 0;
			while (op->cmd[j])
			{
				i = 0;
				while (i++ < level + 1)
					printf("\t");
				printf("%d: %s\n", j, op->cmd[j]);
				++j;
			}
		}
		else
			printf("#### error #####\n");
		op = op->next;
	}
}
