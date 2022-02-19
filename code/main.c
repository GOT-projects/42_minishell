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
int	ft_change_path(t_shell *shell, char *path)
{
	t_env	*node;
	int	i;
	int	j;

	node = ft_get_env_key(shell->env, "USER");
	if (!node)
		return (EXIT_FAILURE);
	i = 0;
	while (path[i])
	{
		j = 0;
		if (node->value[j] == path[i])
		{
			while (node->value[j] == path[i + j])
				j++;
			if (node->value[j] == '\0' &&
				(path[i + j] == '/' || path[i + j] == '\0'))
			{
				ft_strcpy(path, path + j + i);
				return (EXIT_SUCCESS);
			}
		}
		i++;
	}
	return ( EXIT_FAILURE);
}

char	*ft_create_str_read_line(t_shell *shell, int pars)
{
	char	*buf = NULL;
	char	*nb_env;
	char	*nb_pars;
	char	*last_ret;
	char	path[PATH_MAX];

	ft_bzero(path, sizeof(char) * PATH_MAX);
	ft_get_pwd(path);
	nb_env = ft_itoa(shell->t_env->len);
	nb_pars = ft_itoa(pars);
	last_ret = ft_itoa(shell->last_exit_status);
	if (!ft_change_path(shell, path))
		buf = ft_join(" %s | %s | %s | ~%s > ", last_ret, nb_pars, nb_env, path);
	else
		buf = ft_join(" %s | %s | %s | %s > ", last_ret, nb_pars, nb_env, path);
	free(nb_env);
	free(nb_pars);
	free(last_ret);
	return (buf);
}

int	main(int ac, char **av, char **ev)
{
	t_shell	shell;
	char	*line;
	char 	*buf;
	int	pars;

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
	pars = 0;
	buf = ft_create_str_read_line(&shell, pars);
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
				pars = shell.t_pars->len;
				ft_track_free_all(&(shell.t_pars));
			}
		}
		else
			pars = 0;
		free(line);
		free(buf);
		buf = ft_create_str_read_line(&shell, pars);
		line = readline(buf);
	}
	free(line);
	ft_track_free_all(&(shell.t_env));
	rl_clear_history();
	free(buf);
	printf("exit\n");
	return (shell.last_exit_status);
}
