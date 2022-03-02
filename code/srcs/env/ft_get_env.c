/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges <aartiges@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 22:47:31 by aartiges          #+#    #+#             */
/*   Updated: 2022/03/02 22:50:03 by aartiges         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

void	ft_init_oldpwd(t_shell *shell)
{
	char	**cmd;

	cmd = (char **)ft_memalloc(sizeof(char *) * 2);
	cmd[0] = ft_strdup("OLDPWD");
	ft_export(shell, cmd);
	free(cmd[0]);
	free(cmd);
}

/**
* @brief function add all env to list
* 
* @param t_shell *shell
* @param char **ev
* @return  Return (void)
*/
void	ft_init_env(t_shell *shell, char **ev)
{
	char	*key;
	char	*val;
	int		i;
	int		index;

	i = -1;
	val = NULL;
	while (ev[++i])
	{
		index = ft_strichr(ev[i], '=');
		if (index > -1)
		{
			key = ft_strndup(ev[i], index);
			val = ft_strndup(ev[i] + index + 1, ft_strlen(ev[i]) - index - 1);
		}
		else
			key = ft_strndup(ev[i], ft_strlen(ev[i]));
		ft_export_add(shell, key, val);
		free(key);
		if (val != NULL)
			free(val);
	}
	ft_sort_env(shell->env);
}

static int	ft_len_lst_egal(t_env *elem)
{
	int	i;

	i = 0;
	while (elem)
	{
		if (elem->value)
			i++;
		elem = elem->next;
	}
	return (i);
}

/**
* @brief function convert lst to tab
* for use execve 
* /!\ return tab not  track
* 
* @param Param
* @return  Return (tab of lst env)
*/
char	**ft_lst_to_tab(t_shell *shell)
{
	char	**env;
	t_env	*elem;
	size_t	i;

	i = 0;
	elem = shell->env;
	env = (char **)malloc(sizeof(char *) * (ft_len_lst_egal(shell->env) + 1));
	if (!env)
		return (NULL);
	i = 0;
	elem = shell->env;
	while (elem)
	{
		if (elem->value)
		{
			env[i] = ft_join("%s=%s", elem->key, elem->value);
			i++;
		}
		elem = elem->next;
	}
	env[i] = NULL;
	return (env);
}

/**
* @brief function sort alpha lst
* 
* @param t_env *lst
* @return  Return (void)
*/
void	ft_sort_env(t_env *lst)
{
	t_env	*elem;
	char	*tmp;

	while (lst)
	{
		elem = lst;
		while (elem)
		{
			if (ft_strcmp(lst->key, elem->key) > 0)
			{
				tmp = lst->key;
				lst->key = elem->key;
				elem->key = tmp;
				tmp = lst->value;
				lst->value = elem->value;
				elem->value = tmp;
			}
			elem = elem->next;
		}
		lst = lst->next;
	}
}
