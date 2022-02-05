#include "../../includes/mini_shell.h"

/* fonction unset var in list
* @param1 t_envp *lst
* @param2 char *unset
* @return (exit) */
int	ft_unset_var(t_envp *lst, char *unset)
{
	t_envp	*elem;
	t_envp	*tmp;

	elem = lst;
	while (elem)
	{
		if (ft_strncmp(elem->envp, unset, ft_strlen(unset)) == 0)
		{
			tmp = elem;
			if (elem->next != NULL)
				elem->next->prev = tmp->prev;
			if (elem->prev != NULL)
				elem->prev->next = tmp->next;
			return (0);
		}
		elem = elem->next;
	}
	return (0);
}

/* fonction unset var in env
* @param1 struct env
* @param2 char *unset
* @return (bool) */
int	ft_unset(t_shell *env, char *unset)
{
	if (!unset)
		return (0);
	ft_unset_var(env->envp, unset);
	ft_unset_var(env->export, unset);
	return (0);
}
