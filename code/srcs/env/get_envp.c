/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmilhas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 22:56:05 by jmilhas           #+#    #+#             */
/*   Updated: 2022/02/03 22:56:05 by jmilhas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/struct.h"
# include "../../includes/mini_shell.h"

/* function add chainlink var env 
 * @param1 struct env
 * @param2 struct tracker malloc
 * @param3 char **envp
 * @return (bool)*/
t_bool	ft_get_env(t_env *env, t_track *t,char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return (false);
	while (envp[i])
	{
		ft_add_back(&env->envp, ft_create_envp(envp[i], t));
		i++;
	}
	return (true);
}

/* function add chainlink export var 
 * @param1 struct env
 * @param2 struct tracker malloc
 * @param3 char **envp
 * @return (bool)*/
t_bool	ft_get_export(t_env *env, t_track *t, char **envp)
{
	int	i;
	char	*tmp;

	i = 0;
	if (!envp)
		return (false);
	while (envp[i])
	{
		tmp = ft_export_syntax(envp[i]);
		ft_add_back(&env->export, ft_create_envp(tmp, t));
		free(tmp);
		i++;
	}
	ft_sort_export(env->export);
	return (true);
}

/* function add var sorted in export
 * @param1 struct env
 * @param2 struct tracker malloc
 * @param3 char *envp
 * @return (bool)*/
t_bool	ft_sort_export(t_envp *export)
{
	t_envp	*elem;
	t_envp	*t_tmp;	
	char	*tmp;

	elem = export;
	if (!export)
		return (false);
	while (elem)
	{
		t_tmp = elem;
		while (t_tmp)
		{
			if (ft_strcmp(elem->envp, t_tmp->envp) > 0)
			{
				tmp = t_tmp->envp;
				t_tmp->envp = elem->envp;
				elem->envp = tmp;
			}
			t_tmp = t_tmp->next;
		}
		elem = elem->next;
	}
	return (true);	
}

/* function add "" after = in export
 * @param1 char *str
 * @return (str)*/
char	*ft_export_syntax(char *str)
{
	char	*export;
	int	i;
	int	j;

	i = 0;
	j = 0;
	export = (char *)malloc(sizeof(char) * (ft_strlen(str) + 3));
	if (!export)
		return (NULL);
	while (str[i])
	{
		export[i + j] = str[i];
		if (str[i] == '=')
		{
			j++;
			export[i + j] = '"';
		}
		i++;
	}
	export[i + j] = '"';
	export[i + j + 1] = '\0';
	return (export);
}

