#include "includes/mini_shell.h"

void	ft_print(char **tabs)
{
	int	i;

	i = 0;
	while (tabs[i])
	{
		ft_putstr_fd(tabs[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
}

/* int	ft_exec_builtin(t_shell *env, char*cmd, char *args) */
/* { */
/* 	char **conv; */

/* 	if (ft_strcmp(cmd, "export") == 0) */
/* 		ft_export(env, args); */
/* 	if (ft_strcmp(cmd, "env") == 0) */
/* 		ft_env(env); */
/* 	if (ft_strcmp(cmd, "unset") == 0) */
/* 		ft_unset(env, args); */
/* 	if (ft_strcmp(cmd, "clear") == 0) */
/* 		printf("\e[1;1H\e[2J"); */
/* 	if (ft_strcmp(cmd, "tab") == 0) */
/* 	{ */
/* 		conv = ft_lst_to_tab(env->envp); */
/* 		ft_track_tab((void **)conv, env->t_env); */
/* 		ft_print(conv); */
/* 		ft_track_free_tab(env->t_env, (void **)conv); */
/* 	} */
/* 	return (1); */
/* } */

int	main(int ac, char **av, char **ev)
{
	t_shell	shell;
	char	*line;
	char	**args;

	ac = 10 + 1;
	if (ac == 100 && av)
		ac = 100;
	ft_bzero(&shell, sizeof(t_shell));
	shell.t_env = ft_memalloc(sizeof(t_track));
	printf("\e[1;1H\e[2J");
	ft_init_env(&shell, ev);
	while (1)
	{
		printf("env node: %d ", shell.t_env->len);
		line = readline("Minishell > ");
		if (line[0] != '\0' && line)
		{
			args =  ft_split(line, ' ');
			ft_track_tab((void **)args, &(shell.t_env));
			if (ft_strcmp(args[0], "exit") == 0)
				ft_exit(&shell, 0);
			else if (ft_strcmp(args[0], "cd") == 0)
				ft_cd(&shell, &(args[1]));
			else if (ft_strcmp(args[0], "pwd") == 0)
				ft_pwd();
			else if (ft_strcmp(args[0], "env") == 0)
				ft_print_env((shell.env));
			else if (ft_strcmp(args[0], "clear") == 0)
				printf("\e[1;1H\e[2J");
			else if (ft_strcmp(args[0], "export") == 0)
				ft_export(&shell, "lu");
			ft_track_free_tab(&(shell.t_env), (void **)args);
		}
		free(line);
	}
	ft_track_free_all(&(shell.t_env));
	return (0);
}
