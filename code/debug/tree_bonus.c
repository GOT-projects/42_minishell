#include "../includes/mini_shell.h"

void	debug_tree(t_node *op, int level)
{
	int			i;
	int			j;
	t_node	*redir;

	while (op)
	{
		i = 0;
		while (i++ < level)
			printf("\t");
		if (op->genre == PIPE)
		{
			if (op->type_bool != NONE)
			{
				if (op->type_bool == AND)
					printf("and\n");
				else if (op->type_bool == OR)
					printf("or\n");
				i = 0;
				while (i++ < level + 1)
					printf("\t");
				printf("+PIPE\n");
				debug_tree(op->childs, level + 2);
			}
			else
			{
				printf("+PIPE\n");
				debug_tree(op->childs, level + 1);
			}
		}
		else if (op->genre == REDIRECTION)
		{
			if (op->type_bool != NONE)
			{
				if (op->type_bool == AND)
					printf("and\n");
				else if (op->type_bool == OR)
					printf("or\n");
				i = 0;
				while (i++ < level + 1)
					printf("\t");
				printf("+REDIRECTION\n");
				redir = op->lst_redir;
				while (redir)
				{
					i = 0;
					while (i++ < level + 2)
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
				debug_tree(op->childs, level + 3);
			}
			else
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
		}
		else if (op->genre == CMD)
		{
			if (op->type_bool != NONE)
			{
				if (op->type_bool == AND)
					printf("and\n");
				else if (op->type_bool == OR)
					printf("or\n");
				i = 0;
				while (i++ < level + 1)
					printf("\t");
				printf("+CMD\n");
				j = 0;
				while (op->cmd[j])
				{
					i = 0;
					while (i++ < level + 2)
						printf("\t");
					printf("%d: %s\n", j, op->cmd[j]);
					++j;
				}
			}
			else
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
		}
		else if (op->genre == SUB_SHELL)
		{
			if (op->type_bool != NONE)
			{
				if (op->type_bool == AND)
					printf("and\n");
				else if (op->type_bool == OR)
					printf("or\n");
				i = 0;
				while (i++ < level + 1)
					printf("\t");
				printf("+SUB SHELL\n");
				debug_tree(op->childs, level + 2);
			}
			else
			{
				printf("+SUB SHELL\n");
				debug_tree(op->childs, level + 1);
			}
		}
		else if (op->genre == BOOL)
		{
			if (op->type_bool != NONE)
			{
				if (op->type_bool == AND)
					printf("and\n");
				else if (op->type_bool == OR)
					printf("or\n");
				i = 0;
				while (i++ < level + 1)
					printf("\t");
				printf("+BOOL\n");
				debug_tree(op->childs, level + 2);
			}
			else
			{
				printf("+BOOL\n");
				debug_tree(op->childs, level + 1);
			}
		}
		else
			printf("#### error #####\n");
		op = op->next;
	}
}
