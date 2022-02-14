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

/* fonction unset var in env
* @param1 struct s_shell
* @param2 char *unset
* @return (bool) */
int	ft_unset(t_shell *shell, char **unset)
{
	t_env	*node;
	int	i;

	i = -1;
	while (unset[++i])
	{
		node = ft_get_env_key(shell->env, unset[i]);
		if (node)
			ft_unset_node(shell, node->prev, node, node->next);
	}
	return (0);
}
