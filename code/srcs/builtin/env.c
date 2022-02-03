/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmilhas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 22:54:07 by jmilhas           #+#    #+#             */
/*   Updated: 2022/02/03 22:54:11 by jmilhas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/struct.h"
# include "../../includes/mini_shell.h"

/* funtion print variable env
 * @param1 struct env
 * @return (bool)*/
t_bool	ft_env(t_env *env)
{
	t_envp	*elem;

	elem = env->envp;
	if (!env->envp)
		return (false);
	while (elem)
	{
		ft_putstr_fd(elem->envp, 1);
		ft_putstr_fd("\n", 1);
		elem = elem->next;
	}
	return (true);
}
