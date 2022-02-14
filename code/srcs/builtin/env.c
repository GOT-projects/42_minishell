#include "../../includes/mini_shell.h"

/* funtion print variable env
 * @param1 struct s_shell
 * @return (exit)*/
int	ft_env(t_shell *shell)
{
	t_env	*elem;

	elem = shell->env;
	while (elem)
	{
		if (elem->value != NULL)
		{
			ft_putstr_fd(elem->key, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd(elem->value, 1);
			ft_putchar_fd('\n', 1);
		}
		elem = elem->next;
	}
	return (EXIT_SUCCESS);
}
