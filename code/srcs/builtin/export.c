/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmilhas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 22:54:14 by jmilhas           #+#    #+#             */
/*   Updated: 2022/02/03 22:54:17 by jmilhas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "../../includes/struct.h"
# include "../../includes/mini_shell.h"

void	ft_show_export(t_env *env)
{
	t_envp	*elem;

	elem = env->export;
	while (elem)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(elem->envp, 1);
		ft_putstr_fd("\n", 1);
		elem = elem->next;
	}
}

t_bool	ft_check_var(char *s1, char *s2, int c)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i])
	{
		if (s1[i] == s2[i] && s1[i] == c && s2[i] == c)
			return (true);
		i++;
	}
	if (s1[i] == s2[i] && s1[i] == c && s2[i] == c)
		return (true);
	return (false);
}

t_bool	ft_export(t_env *env, char *export)
{
	t_envp	*elem;
	
	elem = env->envp;
	if (!export || export[0] == '\0')
	{
		ft_show_export(env);
		return (true);
	}
	if (ft_strchr(export, '=') == NULL)
		export = ft_track(ft_strjoin(export, "="), env->t_env);
	while (elem)
	{
		if (ft_check_var(elem->envp, export, '=') == true)
		{
			elem->envp = export;
			return (true);
		}
		elem = elem->next;
	}
	ft_add_back(&env->envp, ft_create_envp(export, env->t_env));
	return (true);
}
