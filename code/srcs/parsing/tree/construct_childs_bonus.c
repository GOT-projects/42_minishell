/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construct_childs_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges <aartiges@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 23:16:28 by aartiges          #+#    #+#             */
/*   Updated: 2022/03/02 23:20:20 by aartiges         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mini_shell.h"

/**
 * @brief return a new empty node for the tree (add track on node)
 * 
 * @param shell the shell
 * @return t_node* the node or null if error
 */
t_node	*ft_get_new_node(t_shell *shell)
{
	t_node	*op;

	op = ft_track(malloc(sizeof(t_node)), &(shell->t_pars));
	if (op)
		ft_bzero(op, sizeof(t_node));
	return (op);
}

_Bool	ft_priority_on_parentheses(char *line)
{
	size_t	i;
	int		tmp;
	char	quote;

	i = 0;
	quote = 0;
	tmp = 0;
	while (line && line[i])
	{
		if (!ft_pars_quote(line[i], &quote) && !quote)
		{
			if (line[i] == '(')
				++tmp;
			else if (line[i] == ')')
				--tmp;
			else if (!ft_strchr(SPACES, line[i]) && tmp == 0)
				return (false);
		}
		++i;
	}
	return (true);
}

static void	ft_scotch_priority(char *line, size_t i, t_priority *priority)
{
	if (line[i] == '|')
		*priority = PIPE;
	if ((*priority) != PIPE && (line[i] == '<' || line[i] == '>'))
		*priority = REDIRECTION;
}

/**
 * @brief say which operator in the command line have the priority
 * 
 * @param line the command line
 * @return t_priority the genre of the command line
 */
t_priority	ft_get_top_priority(char *line)
{
	size_t		i;
	t_priority	priority;
	char		quote;
	int			sub_shell;

	if (ft_priority_on_parentheses(line))
		return (SUB_SHELL);
	i = 0;
	quote = 0;
	sub_shell = 0;
	priority = CMD;
	while (line && line[i])
	{
		if (!ft_pars_quote(line[i], &quote) && !quote
			&& !ft_pars_parenthese(line[i], &sub_shell) && sub_shell == 0)
		{
			if (ft_str_start_with(line + i, "||")
				|| ft_str_start_with(line + i, "&&"))
				return (BOOL);
			ft_scotch_priority(line, i, &priority);
		}
		++i;
	}
	return (priority);
}

/**
 * @brief recursive construction of the tree of execution
 * 
 * @param shell the shell
 * @param current the current node
 * @return int 0 if success, 1 if an error occurs
 */
int	ft_construct_child(t_shell *shell, t_node *current)
{
	t_node	*node;

	current->genre = ft_get_top_priority(current->to_parse);
	if (current->genre == PIPE && ft_construct_pipe(shell, current))
		return (1);
	else if (current->genre == REDIRECTION
		&& ft_construct_redirection(shell, current))
		return (1);
	else if (current->genre == CMD && ft_construct_cmd(shell, current))
		return (1);
	else if (current->genre == BOOL && ft_construct_bool(shell, current))
		return (1);
	else if (current->genre == SUB_SHELL
		&& ft_construct_subshell(shell, current))
		return (1);
	ft_track_free(&(shell->t_pars), current->to_parse);
	current->to_parse = NULL;
	node = current->childs;
	while (node)
	{
		if (ft_construct_child(shell, node))
			return (1);
		node = node->next;
	}
	return (0);
}
