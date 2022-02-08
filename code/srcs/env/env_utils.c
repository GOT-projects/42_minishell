
#include "../../includes/mini_shell.h"

t_env	*ft_get_env_key(t_env *lst, const char *key)
{
	t_env	*elem;

	if (!key)
		return (NULL);
	elem = lst;
	while (elem)
	{
		if (!ft_strncmp(elem->key, key, ft_strlen(key)))
			return (elem);
		elem = elem->next;
	}
	return (NULL);
}

char	*ft_get_env_val(t_env *node_var)
{
	if (!node_var)
		return (NULL);
	return (node_var->value);
}

t_env	*ft_replace_node(t_env *node, char *value)
{
	if (!node)
		return (NULL);
	free(node->value);
	node->value = value;
	return (node);
}

/* function export new key value or add new value to node
 * \/!\ key and value will be copy and not free /!\\
 * @param1 t_shell shell
 * @param2 char	*key
 * @param3 char	*new_val
 * @return (stack)*/
int		ft_export_add(t_shell *shell, char *key, char *new_val)
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
	m_val = ft_track((char *)ft_memalloc(sizeof(char) *
		(ft_strlen(new_val) + 1)), &(shell->t_env));
	ft_strcpy(m_val, new_val);
	ft_replace_node(node, m_val);
	return (EXIT_SUCCESS);
}
//int		ft_export_replace("OLDPWD", path);
