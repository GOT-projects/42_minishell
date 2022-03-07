/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges & jmilhas <x@student.42lyon.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 01:19:25 by aartiges &        #+#    #+#             */
/*   Updated: 2022/03/07 01:29:17 by aartiges &       ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void	debug_print_tabs(size_t level)
{
	while (level)
	{
		printf("\t");
		--level;
	}
}

void	debug_print_cmd(t_node *op, size_t level)
{
	size_t	i;

	debug_print_tabs(level);
	printf("+CMD\n");
	i = 0;
	while (op->cmd[i])
	{
		debug_print_tabs(level + 1);
		printf("%zu: %s\n", i, op->cmd[i]);
		++i;
	}
}

void	debug_print_pipe(t_node *op, size_t level)
{
	debug_print_tabs(level);
	printf("+PIPE\n");
	debug_tree(op->childs, level + 1);
}

void	debug_print_redir(t_node *op, size_t level)
{
	t_node	*redir;

	debug_print_tabs(level);
	printf("+REDIRECTION\n");
	redir = op->lst_redir;
	while (redir)
	{
		debug_print_tabs(level + 1);
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
