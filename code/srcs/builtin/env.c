#include "../../includes/mini_shell.h"

/* funtion print variable env
 * @param1 struct env
 * @return (exit)*/
void	ft_env(t_shell *env)
{
	t_envp	*elem;

	elem = env->envp;
	if (!env->envp)
		exit(EXIT_FAILURE);
	while (elem)
	{
		ft_putstr_fd(elem->envp, 1);
		ft_putstr_fd("\n", 1);
		elem = elem->next;
	}
	exit(EXIT_SUCCESS);
}
