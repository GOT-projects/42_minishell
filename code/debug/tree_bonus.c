/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges & jmilhas <x@student.42lyon.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 01:27:59 by aartiges &        #+#    #+#             */
/*   Updated: 2022/03/07 01:34:50 by aartiges &       ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

static void	debug_print_bool_type(t_node *op, size_t level)
{
	debug_print_tabs(level);
	if (op->type_bool == AND)
		printf("and\n");
	else if (op->type_bool == OR)
		printf("or\n");
}

static void	debug_print_bool(t_node *op, size_t level)
{
	debug_print_tabs(level);
	printf("+BOOL\n");
	debug_tree(op->childs, level + 1);
}

static void	debug_print_sub_shell(t_node *op, size_t level)
{
	debug_print_tabs(level);
	printf("+SUB SHELL\n");
	debug_tree(op->childs, level + 1);
}

void	debug_tree(t_node *op, int level)
{
	while (op)
	{
		if (op->type_bool != NONE)
		{
			debug_print_bool_type(op, level);
			++level;
		}
		if (op->genre == PIPE)
			debug_print_pipe(op, level);
		else if (op->genre == REDIRECTION)
			debug_print_redir(op, level);
		else if (op->genre == CMD)
			debug_print_cmd(op, level);
		else if (op->genre == SUB_SHELL)
			debug_print_sub_shell(op, level);
		else if (op->genre == BOOL)
			debug_print_bool(op, level);
		else
			printf("#### error #####\n");
		if (op->type_bool != NONE)
			--level;
		op = op->next;
	}
}
