/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges <aartiges@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 22:46:45 by aartiges          #+#    #+#             */
/*   Updated: 2022/03/02 22:46:52 by aartiges         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

/**
* @brief function found key in list of env
* and return the node found or NULL
* 
* @param t_env	lst 
* @param1 char *key
* @return  Return(node/NULL)
*/
t_env	*ft_get_env_key(t_env *lst, const char *key)
{
	t_env	*elem;

	if (!key)
		return (NULL);
	elem = lst;
	while (elem)
	{
		if (!ft_strcmp(elem->key, key))
			return (elem);
		elem = elem->next;
	}
	return (NULL);
}

/**
* @brief function return the value of the key
* 
* @param t_env *node
* @return  Return (char value);
*/
char	*ft_get_env_val(t_env *node_var)
{
	if (!node_var)
		return (NULL);
	return (node_var->value);
}

/**
* @brief function replace de valur of the node
* 
* @param t_env *node
* @param1 char *value
* @param2 t_env *node
* @return  Return (node);
*/
t_env	*ft_replace_node(t_env *node, char *value, t_track **t)
{
	if (!node)
		return (NULL);
	if (node->value != NULL)
		ft_track_free(t, node->value);
	node->value = value;
	return (node);
}

/* function export new key value or add new value to node
 * \/!\ key and value will be copy and not free /!\\
 * @param1 t_shell shell
 * @param2 char	*key
 * @param3 char	*new_val
 * @return (stack)*/
int	ft_export_add(t_shell *shell, char *key, char *new_val)
{
	t_env	*node;
	char	*m_val;

	node = ft_get_env_key(shell->env, key);
	if (!node)
	{
		ft_add_back(&(shell->env), ft_create_envp(key, new_val,
				&(shell->t_env)));
		return (EXIT_SUCCESS);
	}
	if (new_val != NULL)
	{
		m_val = ft_track((char *)ft_memalloc(sizeof(char)
					* (ft_strlen(new_val) + 1)), &(shell->t_env));
		ft_strcpy(m_val, new_val);
		ft_replace_node(node, m_val, &(shell)->t_env);
		return (EXIT_SUCCESS);
	}
	ft_replace_node(node, new_val, &(shell)->t_env);
	return (EXIT_SUCCESS);
}
