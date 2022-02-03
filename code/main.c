#include "includes/mini_shell.h"

int	main(int ac, char **av, char **ev)
{
	t_shell	*env;
	char	*export1;
	char	*export2;
	char	*export3;

	av[0] = NULL;
	env = ft_memalloc(sizeof(t_shell));
	env->t_env = ft_memalloc(sizeof(t_track));
	export1 = ft_track(ft_memalloc(sizeof(char *) * 50), env->t_env);
	export2 = ft_track(ft_memalloc(sizeof(char *) * 55), env->t_env);
	export3 = ft_track(ft_memalloc(sizeof(char *) * 50), env->t_env);
	export1 = ft_strcpy(export1, "args1");
	export2 = ft_strcpy(export2, "args1= salut");
	export3 = ft_strcpy(export3, "A=nouvelle vallu");
	if (ac == 100)
		return (-1);
	ft_get_env(env, env->t_env, ev);
	ft_get_export(env, env->t_env, ev);
	ft_env(env);
	printf("\n\n\n");
	ft_export(env, "");
	ft_track_free_all(env->t_env);
	free(env);
	return (0);
}
