#include "../../includes/mini_shell.h"

void	ft_print_env(t_env *lst)
{
	t_env	*elem;

	elem = lst;
	while (elem)
	{
		ft_putstr_fd(elem->key, 1);
		ft_putstr_fd(elem->value, 1);
		ft_putstr_fd("\n", 1);
		elem = elem->next;
	}
}

void	ft_init_env(t_shell *shell, char **ev)
{
	char	*key;
	char	*val;
	int	i;
	int	index;

	i = -1;
	while (ev[++i])
	{
		index = ft_strichr(ev[i], '=');
		if (index > -1)
		{
			key = ft_strndup(ev[i], index);
			val = ft_strndup(ev[i] + index, ft_strlen(ev[i]) - index);
			ft_export_add(shell, key, val);
			free(key);
			free(val);
		}
		else
		{
			key = ft_strndup(ev[i], ft_strlen(ev[i]));
			val = NULL;
			ft_export_add(shell, key, val);
			free(key);
		}
	}
}

char	**ft_get_path(t_shell *shell)
{
	t_env	*node;

	node = ft_get_env_key(shell->env, "PATH");
	if (node)
		return (ft_strsplit(node->value, ':'));
	return (NULL);
}
