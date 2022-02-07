#include "../../includes/mini_shell.h"

t_envp	*ft_get_env_key(t_envp *env, char *key); //TODO
char	*ft_get_env_val(t_envp *var_env); //TODO
//ft_export_replace("OLDPWD", path);

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

static int	ft_cd_with_env(t_shell *shell, const char *key_env)
{
	char	*true_path;
	t_envp	*var_env;

	true_path = NULL;
	var_env = ft_get_env_key(shell->envp, key_env);
	if (var_env)
		true_path = ft_envp_get_val(var_env);
	if (!var_env || !true_path)
	{
		ft_putstr_fd("cd: « ", 2);
		ft_putstr_fd(key_env, 2);
		ft_putstr_fd("» not defined\n", 2);
		return (1);
	}
	ft_cd_pwd_path(true_path);
	free_envp(var_env);
	free(true_path);
	return (errno);
}

static int	ft_cd_precd(t_shell *shell, t_envp **var_env[2], char *path)
{
	(*var_env)[0] = ft_get_env_key(shell->export, "PWD");
	if ((*var_env)[0])
	{
		(*var_env)[1] = ft_get_env_key(shell->export, "OLDPWD");
		if ((*var_env)[1] && ft_get_pwd(path))
			return (errno);
	}
	return (0);
}

static int	ft_cd_postcd(t_shell *shell, t_envp **var_env[2], char *path)
{
	if ((*var_env)[1])
		ft_export_replace("OLDPWD", path);
	if (ft_get_pwd(path))
		return (errno);
	ft_export_replace("PWD", path);
	return (0);
}

int	ft_cd(t_shell *shell, char **paths)
{
	char	path[_PC_PATH_MAX];
	t_envp	*var_env[2];
	int		ret;

	errno = 0;
	if (ft_nb_args(paths) > 1)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (1);
	}
	ft_bzero(path, _PC_PATH_MAX * sizeof(char));
	ret = ft_cd_precd(shell, &var_env, path);
	if (!ret && !paths[0])
		ret = ft_cd_with_env(shell, "HOME");
	else if (!ret && ft_strcmp(paths[0], "-"))
		ret = ft_cd_with_env(shell, "OLDPWD");
	else if (!ret)
		ret = ft_cd_pwd_path(paths[0]);
	if (!ret && var_env[0])
		ret = ft_cd_postcd(shell, &var_env, path);
	return (ret);
}
