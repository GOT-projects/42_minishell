#include "../../includes/mini_shell.h"

static void	ft_print_exp(t_env *lst)
{
	t_env	*elem;

	elem = lst;
	while (elem)
	{
		ft_putstr_fd("declare -x ", 1);
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
int	ft_export(t_shell *shell, char **exp)
{
	char	*key;
	char	*val;
	int	i;
	int	index;

	i = 0;
	/* if (exp) */
	/* { */
		ft_print_exp(shell->env);
	/* 	return (EXIT_SUCCESS); */
	/* } */
	while (exp[++i])
	{
		index = ft_strichr(exp[i], '=');
		if (index > -1)
		{
			key = ft_strndup(exp[i], index);
			val = ft_strndup(exp[i] + index, ft_strlen(exp[i]) - index);
			printf("%s\n", val);
			ft_export_add(shell, key, val);
		}
		else
		{
			key = ft_strndup(exp[i], ft_strlen(exp[i]));
			val = ft_strdup("");
			ft_export_add(shell, key, val);
		}
		free(key);
		free(val);
	}

	return (0);
}
