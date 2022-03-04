/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_prg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges <aartiges@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 19:42:40 by aartiges &        #+#    #+#             */
/*   Updated: 2022/03/03 23:31:17 by aartiges         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

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
 * @param true_path array of path (for the norm)
 * @return ** char* -- if the path dosn't exist or if the file is not executable
 * return NULL and the integer ret is set with the error code
 * else if the file exist and is executable return a !!copy!! of the command
 * and set the integer ret is set to 0 (to free)
 */
static char	*ft_check_prg_paths(char **cmd, int *ret, char **paths,
	char *true_path[3])
{
	size_t	i;

	i = 0;
	while (!true_path[1] && paths && paths[i])
	{
		true_path[0] = ft_strjoin(paths[i++], "/");
		true_path[1] = ft_strjoin(true_path[0], cmd[0]);
		if (!true_path[0] || !true_path[1])
		{
			*ret = errno;
			ft_free_2d(true_path);
			return (NULL);
		}
		free(true_path[0]);
		if (!access(true_path[1], F_OK) && !access(true_path[1], X_OK))
			*ret = 0;
		else
		{
			if (!access(true_path[1], F_OK) && access(true_path[1], X_OK))
				*ret = ERR_403_EXEC;
			free(true_path[1]);
			true_path[1] = NULL;
		}
	}
	return (true_path[1]);
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
	char	*true_path[3];

	paths = ft_get_path(shell);
	if (!paths)
	{
		*ret = ERR_404_EXEC;
		return (NULL);
	}
	ft_bzero(true_path, 3 * sizeof(char *));
	ft_check_prg_paths(cmd, ret, paths, true_path);
	ft_free_2d(paths);
	return (true_path[1]);
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

	env = ft_lst_to_tab(shell);
	pid = fork();
	if (pid < 0)
	{
		perror(cmd[0]);
		return (errno);
	}
	else if (pid == 0)
	{
		exec_mode_sub_process();
		if (!env && shell->env)
			ft_putstr_fd("No space available\n", 2);
		if (!env && shell->env)
			return (1);
		execve(path_prg, cmd, env);
		perror(path_prg);
		exit(1);
	}
	waitpid(pid, &status, 0);
	ft_free_2d(env);
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
	char	*true_path;
	int		ret;

	ret = ERR_404_EXEC;
	true_path = NULL;
	if (ft_strchr(cmd[0], '/'))
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
