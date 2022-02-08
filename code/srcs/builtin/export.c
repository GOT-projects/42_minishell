#include "../../includes/mini_shell.h"

static void	ft_print_exp(t_env *lst)
{
	t_env	*elem;

	elem = lst;
	while (elem)
	{
		ft_putstr_fd(elem->key, 1);
		if (ft_strlen(elem->value) > 1)
		{
			ft_putchar_fd('"', 1);
			ft_putstr_fd(elem->value, 1);
			ft_putchar_fd('"', 1);
		}
		ft_putchar_fd('\n', 1);
		elem = elem->next;
	}
}

/* function builtin de export
 * @param1 t_shell shell
 * @param2 char	*string
 * @return (exit)*/
int	ft_export(t_shell *shell, char *export)
{
	export = NULL;
	if (export != NULL)
		return (1);
	ft_print_exp(shell->env);
	return (0);
}
