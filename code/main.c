#include "includes/mini_shell.h"

int	ft_exec_builtin(t_shell *env, char*cmd, char *args)
{
	if (ft_strcmp(cmd, "export") == 0)
		ft_export(env, args);
	if (ft_strcmp(cmd, "env") == 0)
		ft_env(env);
	if (ft_strcmp(cmd, "clear") == 0)
		printf("\e[1;1H\e[2J");
	return (1);
}


int	main(int ac, char **av, char **ev)
{
	t_shell	*env;
	char	*line;
	char	**args;

	ac = 10 + 1;
	if (ac == 100 && av)
		ac = 100;
	env = ft_memalloc(sizeof(t_shell));
	env->t_env = ft_memalloc(sizeof(t_track));
	ft_get_env(env, env->t_env, ev);
	ft_get_export(env, env->t_env, ev);
	printf("\e[1;1H\e[2J");
	while (1)
	{
		line = readline("🔞 Minishell> ");
		if (line[0] != '\0' && line)
		{
			args = ft_split(line, ' ');
			ft_track_tab((void **)args, env->t_env);
			free(line);
			if (ft_strcmp(args[0], "exit") == 0)
				ft_exit(env, 0);
			ft_exec_builtin(env, args[0], args[1]);
			ft_track_free_tab(env->t_env, (void **)args);
		}
	}
	ft_track_free_all(env->t_env);
	free(env);
	return (0);
}
