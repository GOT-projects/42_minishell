/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges <aartiges@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 23:13:55 by aartiges          #+#    #+#             */
/*   Updated: 2022/03/02 23:13:57 by aartiges         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mini_shell.h"

static int	ft_create_and(t_shell *shell, t_node **op, char **split_and)
{
	t_node	*new;
	size_t	i;

	i = 0;
	while (split_and[i])
	{
		new = ft_get_new_node(shell);
		if (!new)
		{
			while (split_and[i])
				free(split_and[i++]);
			free(split_and);
			return (1);
		}
		new->type_bool = AND;
		new->to_parse = ft_track(split_and[i], &(shell->t_pars));
		ft_op_add_back(op, new);
		++i;
	}
	(*op)->type_bool = NONE;
	free(split_and);
	return (0);
}

size_t	ft_split_len(char **split)
{
	size_t	i;

	i = 0;
	while (split && split[i])
		++i;
	return (i);
}

int	ft_add_or(t_shell *shell, char **split, t_node *op, size_t size)
{
	size_t	i;
	t_node	*new;

	ft_track_free(&(shell->t_pars), op->to_parse);
	op->to_parse = ft_track(split[0], &(shell->t_pars));
	i = size - 1;
	while (i > 0)
	{
		new = ft_get_new_node(shell);
		if (!new)
		{
			while (!new && i > 0)
				free(split[i--]);
			free(split);
			return (1);
		}
		new->to_parse = ft_track(split[i], &(shell->t_pars));
		new->type_bool = OR;
		new->next = op->next;
		op->next = new;
		--i;
	}
	return (0);
}

int	ft_create_or(t_shell *shell, t_node *op)
{
	char	**split;
	size_t	i;

	while (op)
	{
		split = ft_split_str(op->to_parse, "||");
		if (!split)
			return (1);
		i = ft_split_len(split);
		if (i > 1)
		{
			if (ft_add_or(shell, split, op, i))
				return (1);
			free(split);
		}
		else
			ft_free_2d(split);
		op = op->next;
	}
	return (0);
}

int	ft_construct_bool(t_shell *shell, t_node *current)
{
	char	**split_and;
	t_node	*op;

	split_and = ft_split_str(current->to_parse, "&&");
	if (!split_and)
		return (1);
	op = NULL;
	if (ft_create_and(shell, &op, split_and))
		return (1);
	if (ft_create_or(shell, op))
		return (1);
	current->childs = op;
	return (0);
}
