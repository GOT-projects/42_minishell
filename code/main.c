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

	if (ac > 1)
	{
		ft_putstr_fd(av[0], 2);
		ft_putstr_fd("to many arguments\n", 2);
		return (1);
	}
	ft_bzero(&shell, sizeof(t_shell));
	line = NULL;
	shell.t_env = ft_memalloc(sizeof(t_track));
	printf("\e[1;1H\e[2J");
	ft_init_env(&shell, ev);
	// signal interactive
	interactive_mode();
	//printf("env node: %d ", shell.t_env->len);
	line = readline("Minishell > ");
	while (line)
	{
		//printf("env node: %d ", shell.t_env->len);
		//printf("%s\n", line);
		if (line && line[0] != '\0')
		{
			add_history(line);
			if (ft_check_syntax_prompt(line))
				shell.last_exit_status = 1;
			else
			{
				shell.t_pars = ft_memalloc(sizeof(t_track));
				if (!shell.t_pars)
				{
					ft_putstr_fd("parsing allocation problem [track]\n", 2);
					ft_track_free_all(&(shell.t_env));
					rl_clear_history();
					return (1);
				}
				if (ft_parse(&shell, line))
				{
					ft_putstr_fd("oups parsing error\n", 2);
					shell.last_exit_status = 1;
				}
				else
				{
					//debug_tree(shell.operation, 0);
					ft_exec(&shell, shell.operation);
				}
				ft_track_free_all(&(shell.t_pars));
			}
		}
		free(line);
		line = readline("Minishell > ");
	}
	ft_track_free_all(&(shell.t_env));
	rl_clear_history();
	printf("exit\n");
	return (shell.last_exit_status);
}
