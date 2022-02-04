#include "../../includes/mini_shell.h"

/* function printf export var
 * @param1 t_shell env
 * @return (exit)*/
void	ft_show_export(t_shell *env)
{
	t_envp	*elem;

	elem = env->export;
	while (elem)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(elem->envp, 1);
		ft_putstr_fd("\n", 1);
		elem = elem->next;
	}
	exit(EXIT_SUCCESS);
}

/* function cherche var dans list 
 * et la remplace par la nouvelle valeur
 * @param1 t_envp lst
 * @param2 char	*string
 * @return (void)*/
void	ft_replace_export(t_envp *lst, char *s)
{
	t_envp	*elem;
	int	index;
	int	i;

	i = -1;
	elem = lst;
	index = ft_check_lst(lst, s);
	while (i++ < index -1)
		elem = elem->next;
	elem->envp = s;
}

/* function add dans export vairable 
 * @param1 t_shell env
 * @param2 char	*string
 * @return (exit)*/
void	ft_export_var(t_shell *env, char*s)
{
		if (ft_check_lst(env->export, s) > -1)
		{
			ft_replace_export(env->export, s);
			exit(EXIT_SUCCESS);
		}
		ft_add_back(&env->export, ft_create_envp(s, env->t_env));
		ft_sort_export(env->export);
		exit(EXIT_SUCCESS);
}

/* function builtin de export
 * @param1 t_shell env
 * @param2 char	*string
 * @return (exit)*/
int	ft_export(t_shell *env, char *export)
{
	t_envp	*elem;

	elem = env->envp;
	if (!export || export[0] == '\0')
		ft_show_export(env);
	if (ft_strichr(export, '=') < 0)
		ft_export_var(env, export);
	if (ft_check_lst(env->export, export) > -1 || ft_check_lst(env->envp, export) > -1)
	{
		if (ft_check_lst(env->export, export) > -1)
			ft_replace_export(env->export, export);
		if (ft_check_lst(env->envp, export) > -1)
			ft_replace_export(env->envp, export);
	}
	if (ft_check_lst(env->export, export) == -1)
		ft_add_back(&env->export, ft_create_envp(export, env->t_env));
	if (ft_check_lst(env->envp, export) == -1)
		ft_add_back(&env->envp, ft_create_envp(export, env->t_env));
	ft_sort_export(env->export);
	exit(EXIT_SUCCESS);
}
