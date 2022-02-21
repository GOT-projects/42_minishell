/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges & jmilhas <x@student.42lyon.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 19:36:08 by aartiges &        #+#    #+#             */
/*   Updated: 2022/02/21 19:36:14 by aartiges &       ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

/* function check error export
 * @param1 char *export
 * @return (exit)*/
static int	ft_error_export(char *exp)
{
	int	i;

	i = 0;
	if (exp && ft_isalpha(exp[i]) == 0)
	{
		ft_putstr_fd("Minishell: export: '", 2);
		ft_putstr_fd(exp, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (EXIT_FAILURE);
	}
	i++;
	while (exp[i] && exp[i] != '=')
	{
		if (!ft_isalnum(exp[i]) && !ft_isalpha(exp[i]))
		{
			ft_putstr_fd("Minishell: export: '", 2);
			ft_putstr_fd(exp, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

/* function print export
 * @param1 t_env lst
 * @return (void)*/
static void	ft_print_exp(t_env *lst)
{
	t_env	*elem;

	elem = lst;
	while (elem)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(elem->key, 1);
		if (elem->value)
		{
			ft_putchar_fd('=', 1);
			ft_putchar_fd('"', 1);
			ft_putstr_fd(elem->value, 1);
			ft_putchar_fd('"', 1);
		}
		ft_putchar_fd('\n', 1);
		elem = elem->next;
	}
}

/* function add var in export
 * @param1 t_shell shell
 * @param2 int index
 * @param3 char *exp
 * @return (void)*/
static void	ft_add_export(t_shell *shell, int index, char *exp)
{
	char	*key;
	char	*val;

	if (index > -1)
	{
		key = ft_strndup(exp, index);
		val = ft_strndup(exp + index + 1, ft_strlen(exp) - index - 1);
		ft_export_add(shell, key, val);
	}
	else
	{
		key = ft_strndup(exp, ft_strlen(exp));
		val = NULL;
		ft_export_add(shell, key, val);
	}
	free(key);
	free(val);
}

/* function builtin de export
 * @param1 t_shell shell
 * @param2 char	*string
 * @return (exit)*/
int	ft_export(t_shell *shell, char **exp)
{
	int	i;
	int	index;

	i = 0;
	if (!exp[0])
	{
		ft_print_exp(shell->env);
		return (EXIT_SUCCESS);
	}
	while (exp[i])
	{
		if (ft_error_export(exp[i]))
			return (1);
		index = ft_strichr(exp[i], '=');
		ft_add_export(shell, index, exp[i]);
		i++;
	}
	ft_sort_env(shell->env);
	return (EXIT_SUCCESS);
}
