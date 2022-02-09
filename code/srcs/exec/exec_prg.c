#include "../../includes/mini_shell.h"

/**
 * @brief function call only if the command is a path (like ./a.out or
 * /tmp/a.out) -- check if the command exist
 * 
 * @param cmd the path of the command
 * @param ret a pointer on an interger that correspond of the exit status of
 * the command
 * @return ** char* -- if the path dosn't exist or if the file is not executable
 * return NULL and the integer ret is set with the error code
 * else if the file exist and is executable return a !!copy!! of the command
 * and set the integer ret is set to 0 (to free)
 */
static char	*ft_check_prg_path_relative(char *cmd, int *ret)
{
	if (!access(cmd, F_OK))
	{
		if (access(cmd, X_OK))
		{
			*ret = ERR_403_EXEC;
			return (NULL);
		}
		else
		{
			*ret = 0;
			return (ft_strdup(cmd));
		}
	}
	*ret = ERR_404_EXEC;
	return (NULL);
}

/**
 * @brief function call by ft_check_prg_path
 * 
 * @param cmd arguments array of the command (like "ls" "-l" "/")
 * @param ret a pointer on an interger that correspond of the exit status of
 * the command
 * @param paths array of path that are in environnement variable
 * @return ** char* -- if the path dosn't exist or if the file is not executable
 * return NULL and the integer ret is set with the error code
 * else if the file exist and is executable return a !!copy!! of the command
 * and set the integer ret is set to 0 (to free)
 */
static char	*ft_check_prg_paths(char **cmd, int *ret, char **paths)
{
	size_t	i;
	char	*true_path;

	true_path = NULL;
	i = 0;
	while (!true_path && paths[i])
	{
		true_path = ft_strjoin(paths[i++], cmd[0]);
		if (!true_path)
		{
			free(paths);
			*ret = errno;
			return (NULL);
		}
		if (!access(true_path, F_OK) && !access(true_path, X_OK))
			*ret = 0;
		else if (!access(true_path, F_OK) && access(true_path, X_OK))
			*ret = ERR_403_EXEC;
		else
		{
			free(true_path);
			true_path = NULL;
		}
	}
	return (true_path);
}

/**
 * @brief function call only if the command is not a path (like ls or cat)
 * -- check if the command exist
 * 
 * @param shell the shell, for get the env array
 * @param cmd arguments array of the command (like "ls" "-l" "/")
 * @param ret a pointer on an interger that correspond of the exit status of
 * the command
 * @return char* -- if the path dosn't exist or if the file is not executable
 * return NULL and the integer ret is set with the error code
 * else if the file exist and is executable return a !!copy!! of the command
 * and set the integer ret is set to 0 (to free)
 */
static char	*ft_check_prg_path(t_shell *shell, char **cmd, int *ret)
{
	char	**paths;
	char	*true_path;

	paths = ft_get_env_paths(shell); //TODO
	if (!paths)
	{
		*ret = errno;
		return (NULL);
	}
	true_path = ft_check_prg_paths(cmd, ret, paths);
	free_tab(paths); //TODO
	return (true_path);
}

/**
 * @brief execute a command (we supose that the path_prg is correct)
 * 
 * @param shell the shell for get the environnement array
 * @param path_prg the path of the program
 * @param cmd arguments array of the command (like "ls" "-l" "/")
 * @return int the exit status of the program
 */
static int	ft_exec_prg_final(t_shell *shell, char *path_prg, char **cmd)
{
	char	**env;
	pid_t	pid;
	int		status;

	env = ft_get_env_tab(shell); //TODO
	pid = fork();
	if (pid < 0)
	{
		perror(cmd[0]);
		return (errno);
	}
	else if (pid == 0)
	{
		if (!env && shell->env)
		{
			ft_putstr_fd("No space available\n", 2);
			return (1);
		}
		execve(path_prg, cmd, env);
		return (1);
	}
	waitpid(pid, &status, 0/*WCONTINUED*/);
	free_tab(env);
	return (ft_error_exit_process(cmd[0], status));
}

/**
 * @brief search the program and execute the command
 * 
 * @param shell the shell to get the environnement array and paths dir
 * @param cmd arguments array of the command (like "ls" "-l" "/")
 * @return int the exit status of the command cmd
 */
int	ft_exec_prg(t_shell *shell, char **cmd)
{
	size_t	i;
	char	**paths;
	char	*true_path;
	int		ret;

	ret = ERR_404_EXEC;
	true_path = NULL;
	if (strchr(cmd[0], '/'))
		true_path = ft_check_prg_path_relative(cmd[0], &ret);
	else
		true_path = ft_check_prg_path(shell, cmd, &ret);
	if (true_path)
	{
		ret = ft_exec_prg_final(shell, true_path, cmd);
		free(true_path);
	}
	else
		ft_prg_error_research_path(cmd, ret);
	return (ret);
}
