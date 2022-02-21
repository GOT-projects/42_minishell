/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_childs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges & jmilhas <x@student.42lyon.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 20:43:08 by aartiges &        #+#    #+#             */
/*   Updated: 2022/02/21 20:43:09 by aartiges &       ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mini_shell.h"

/**
 * @brief add at the back of the list
 * 
 * @param ops a pointer on the pointer on the 1st element of the list
 * @param node the new element
 */
void	ft_op_add_back(t_node **ops, t_node *node)
{
	t_node	*tmp;

	if (*ops == NULL)
		*ops = node;
	else
	{
		tmp = *ops;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
}

/**
 * @brief get the number of bro for a node of the tree
 * 
 * @param childs the first node of the list
 * @return size_t the size of the list
 */
size_t	ft_op_bro_size(t_node *childs)
{
	size_t	i;

	i = 0;
	while (childs)
	{
		++i;
		childs = childs->next;
	}
	return (i);
}
