/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges & jmilhas <x@student.42lyon.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 01:19:18 by aartiges &        #+#    #+#             */
/*   Updated: 2022/03/07 01:19:20 by aartiges &       ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void	debug_tree(t_node *op, int level)
{
	while (op)
	{
		if (op->genre == PIPE)
			debug_print_pipe(op, level);
		else if (op->genre == REDIRECTION)
			debug_print_redir(op, level);
		else if (op->genre == CMD)
			debug_print_cmd(op, level);
		else
			printf("#### error #####\n");
		op = op->next;
	}
}
