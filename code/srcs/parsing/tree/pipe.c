/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges & jmilhas <x@student.42lyon.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 20:43:40 by aartiges &        #+#    #+#             */
/*   Updated: 2022/02/21 20:43:41 by aartiges &       ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mini_shell.h"

/**
 * @brief create the childs nodes that will be pipe and add them to the tree
 * 
 * @param shell the shell
 * @param current the current node of the pipe
 * @return int 1 if error, 0 else
 */
int	ft_construct_pipe(t_shell *shell, t_node *current)
{
	t_node	*tmp;
	char	**split;
	size_t	i;

	split = ft_split_str(current->to_parse, "|");
	if (!split)
		return (1);
	i = 0;
	while (split[i])
	{
		tmp = ft_get_new_node(shell);
		if (!tmp)
		{
			ft_free_2d(split);
			return (1);
		}
		tmp->to_parse = split[i++];
		ft_op_add_back(&(current->childs), tmp);
	}
	i = 0;
	while (split[i])
		ft_track(split[i++], &(shell->t_pars));
	free(split);
	return (0);
}
