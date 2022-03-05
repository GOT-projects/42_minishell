/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_shell_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges & jmilhas <x@student.42lyon.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 23:14:02 by aartiges          #+#    #+#             */
/*   Updated: 2022/03/04 21:41:45 by aartiges &       ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mini_shell.h"

int	ft_construct_subshell(t_shell *shell, t_node *current)
{
	size_t	start;
	size_t	end;
	t_node	*new;

	new = ft_get_new_node(shell);
	if (!new)
		return (1);
	start = 0;
	while (current->to_parse[start] && current->to_parse[start] != '(')
		++start;
	++start;
	end = ft_strlen(current->to_parse);
	while (end > start && current->to_parse[end] != ')')
		--end;
	new->to_parse = ft_track(ft_substr(current->to_parse, start,
				end - start), &(shell->t_pars));
	if (!(new->to_parse))
		return (1);
	current->childs = new;
	return (0);
}
