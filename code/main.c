#include "includes/mini_shell.h"

int	main(int ac, char **av, char **ev)
{
	t_shell	shell;
	char	*line;
	char 	*buf;

	if (ac > 1)
	{
		ft_putstr_fd(av[0], 2);
		ft_putstr_fd("to many arguments\n", 2);
		return (1);
	}
	interactive_mode();
	ft_bzero(&shell, sizeof(t_shell));
	line = NULL;
	shell.t_env = ft_memalloc(sizeof(t_track));
	printf("\e[1;1H\e[2J");
	ft_init_env(&shell, ev);
	ft_init_oldpwd(&shell);
	buf = ft_create_str_read_line(&shell);
	line = readline(buf);
	while (line)
	{
		if (line && line[0] != '\0')
		{
			add_history(line);
			if (!ft_strcmp(line, "q"))
				break;
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
					exec_mode();
					ft_exec(&shell, shell.operation);
					interactive_mode();
				}
				ft_track_free_all(&(shell.t_pars));
			}
		}
		free(line);
		free(buf);
		buf = ft_create_str_read_line(&shell);
		line = readline(buf);
	}
	free(line);
	ft_track_free_all(&(shell.t_env));
	rl_clear_history();
	free(buf);
	printf("exit\n");
	return (shell.last_exit_status);
}
