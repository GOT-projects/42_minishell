/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges <aartiges@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 22:46:18 by aartiges          #+#    #+#             */
/*   Updated: 2022/03/02 22:46:20 by aartiges         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

static void	ft_unset_node(t_shell *shell, t_env *prev, t_env *curr, t_env *next)
{
	if (prev == NULL)
		next->prev = NULL;
	else if (next == NULL)
		prev->next = NULL;
	else
	{
		prev->next = next;
		next->prev = prev;
	}
	ft_track_free(&(shell->t_env), curr->key);
	if (curr->value != NULL)
		ft_track_free(&(shell->t_env), curr->value);
	ft_track_free(&(shell->t_env), curr);
}

static void	ft_print_unset(char *unset)
{
	ft_putstr_fd("minishell unset : `", 2);
	ft_putstr_fd(unset, 2);
	ft_putstr_fd("': not valid identifier", 2);
	ft_putstr_fd("\n", 2);
}

/* fonction unset var in env
* @param1 struct s_shell
* @param2 char *unset
* @return (bool) */
int	ft_unset(t_shell *shell, char **unset)
{
	t_env	*node;
	int		i;

	i = 0;
	while (unset[i])
	{
		if (!ft_is_shell_var(unset[i]))
		{
			ft_print_unset(unset[i]);
			return (1);
		}
		node = ft_get_env_key(shell->env, unset[i]);
		if (node)
			ft_unset_node(shell, node->prev, node, node->next);
		i++;
	}
	return (0);
}
