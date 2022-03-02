/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges <aartiges@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 19:28:25 by aartiges &        #+#    #+#             */
/*   Updated: 2022/03/02 23:56:03 by aartiges         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

/**
 * @brief function that apply the changement of directory
 * 
 * @param path the new path
 * @return int 0 if sucess, else > 0 number
 */
static int	ft_cd_pwd_path(char *path)
{
	if (chdir(path) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		perror(path);
		return (errno);
	}
	return (0);
}

/**
 * @brief function that change the current directory, with the new path that
 * correspond to an environnement variable
 * 
 * @param shell the shell
 * @param key_env the name of the variable in the env
 * @return int 0 if success, else > 0
 */
static int	ft_cd_with_env(t_shell *shell, const char *key_env)
{
	char	*true_path;
	t_env	*var_env;

	true_path = NULL;
	var_env = ft_get_env_key(shell->env, key_env);
	if (var_env)
		true_path = ft_get_env_val(var_env);
	if (!var_env || !true_path)
	{
		ft_putstr_fd("cd: « ", 2);
		ft_putstr_fd(key_env, 2);
		ft_putstr_fd("» not defined\n", 2);
		return (1);
	}
	ft_cd_pwd_path(true_path);
	return (errno);
}

/**
 * @brief take a save of PWD and OLDPWD env var for the execution
 * 
 * @param shell the shell
 * @param var_env pointer on array that will contain PWD and OLDPWD
 * @return int 0 if success, else > 0
 */
static int	ft_cd_precd(t_shell *shell, t_env *(*var_env)[2])
{
	(*var_env)[0] = ft_get_env_key(shell->env, "PWD");
	if ((*var_env)[0])
	{
		(*var_env)[1] = ft_get_env_key(shell->env, "OLDPWD");
	}
	return (0);
}

/**
 * @brief funtion that update PWD and OLDPWD var at the end of the cd
 * 
 * @param shell the shell
 * @param var_env the nodes of PWD and OLDPWD
 * @param path the new OLDPWD
 * @return int 0 if success, else > 0
 */
static int	ft_cd_postcd(t_shell *shell, t_env *(*var_env)[2], char *path)
{
	if ((*var_env)[1])
		ft_export_add(shell, "OLDPWD", ((*var_env)[0])->value);
	if (ft_get_pwd(path))
		return (errno);
	ft_export_add(shell, "PWD", path);
	return (0);
}

/**
 * @brief cd builtin
 * 
 * @param shell the shell
 * @param paths the args of the command
 * @return int 0 if success, else > 0
 */
int	ft_cd(t_shell *shell, char **paths)
{
	char	path[PATH_MAX];
	t_env	*var_env[2];
	int		ret;

	errno = 0;
	if (ft_nb_args(paths) > 1)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (1);
	}
	var_env[1] = NULL;
	ret = ft_cd_precd(shell, &var_env);
	if (!ret && !paths[0])
		ret = ft_cd_with_env(shell, "HOME");
	else if (!ret && !ft_strcmp(paths[0], "-"))
		ret = ft_cd_with_env(shell, "OLDPWD");
	else if (!ret)
		ret = ft_cd_pwd_path(paths[0]);
	if (!ret && var_env[0])
		ret = ft_cd_postcd(shell, &var_env, path);
	return (ret);
}
