#include "includes/mini_shell.h"

void	ft_print(char **tabs)
{
	int	i;

	i = 0;
	while (tabs[i])
	{
		printf("%s\n", tabs[i]);
		i++;
	}
}

int	main(int ac, char **av, char **ev)
{
	t_shell	shell;
	char	*line;
	char	**args;
	char 	**env;

	ac = 10 + 1;
	if (ac == 100 && av)
		ac = 100;
	ft_bzero(&shell, sizeof(t_shell));
	shell.t_env = ft_memalloc(sizeof(t_track));
	printf("\e[1;1H\e[2J");
	ft_init_env(&shell, ev);
	env = ft_lst_to_tab(&shell);
	ft_track_tab((void **)env, &(shell).t_env);
	ft_print(env);
	while (1)
	{
		printf("env node: %d ", shell.t_env->len);
		line = readline("Minishell > ");
		add_history(line);
		if (line[0] != '\0' && line)
		{
			args =  ft_strsplit(line, ' ');
			ft_track_tab((void **)args, &(shell.t_env));
			if (ft_strcmp(args[0], "exit") == 0)
				ft_exit(&shell, 0);
			else if (ft_strcmp(args[0], "cd") == 0)
				ft_cd(&shell, &(args[1]));
			else if (ft_strcmp(args[0], "pwd") == 0)
				ft_pwd();
			else if (ft_strcmp(args[0], "env") == 0)
				ft_env(&shell);
			else if (ft_strcmp(args[0], "clear") == 0)
				printf("\e[1;1H\e[2J");
			else if (ft_strcmp(args[0], "export") == 0)
				ft_export(&shell, args);
			else if (ft_strcmp(args[0], "unset") == 0)
				ft_unset(&shell, args);
			ft_track_free_tab(&(shell.t_env), (void **)args);
		}
		free(line);
	}
	clear_history();
	ft_track_free_all(&(shell.t_env));
	return (0);
}
