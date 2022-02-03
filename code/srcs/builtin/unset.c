/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmilhas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 22:54:30 by jmilhas           #+#    #+#             */
/*   Updated: 2022/02/03 22:54:33 by jmilhas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/struct.h"
# include "../../includes/mini_shell.h"

/* fonction unset var in env
* @param1 struct env
* @param2 char *unset
* @return (bool) */
t_bool	ft_unset(t_env *env, char *unset)
{
	t_envp	*elem;
	t_envp	*tmp;

	elem = env->envp;
	if (!unset)
		return (false);
	if (ft_strchr(unset, '=') == NULL)
		unset = ft_track(ft_strjoin(unset, "="), env->t_env);
	if (ft_check_var(elem->envp, unset, '=') == true)
	{
		env->envp = elem->next;
		env->envp->prev = NULL;
		return (true);
	}
	while (elem)
	{
		if (ft_check_var(elem->envp, unset, '=') == true)
		{
			tmp = elem;
			if (elem->next != NULL)
				elem->next->prev = tmp->prev;
			if (elem->prev != NULL)
				elem->prev->next = tmp->next;
			return (true);
		}
		elem = elem->next;
	}
	return (false);
}
