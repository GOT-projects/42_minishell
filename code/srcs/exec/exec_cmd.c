#include "../../includes/mini_shell.h"

int	ft_exec_prg(t_shell *shell, char **cmd)
{
	size_t	i;
	char	**paths;
	char	*true_path;
	int		ret;

	ret = ERR_404_EXEC;
	true_path = NULL;
	if (strchr(cmd[0], '/'))
	{
		if (/*exist*/)
		{
			if (!access(cmd[0], X_OK))
				true_path = cmd[0];
			else
				ret = ERR_403_EXEC;
		}
	}
	else
	{
		paths = ft_get_env_paths(shell);
		if (!paths)
		{
			//TODO
		}
		i = 0;
		while (!true_path && paths[i])
		{
			true_path = ft_strjoin(paths[i++], cmd[0]);
			if (!true_path)
				// TODO free
			if (access(true_path, X_OK))
			{
				free(true_path);
				true_path = NULL;
			}
		}
	}
	if (true_path)
		// create sub process
	else
	{
		ft_putstr_fd(cmd[0], 2);
		if (ret == ERR_403_EXEC)
			ft_putstr_fd(": Permission denied\n", 2);
		if (strchr(cmd[0], '/') && ret == ERR_404_EXEC)
			ft_putstr_fd(": No such file or directory\n", 2);
		else if (strchr(cmd[0], '/') && ret == ERR_403_EXEC)
			ft_putstr_fd(": Command not found\n", 2);
	}
	return (ret);
}

int	ft_exec_cmd(t_shell *shell, char **cmd)
{
	if (!cmd[0])
	{
		ft_putstr_fd("No command found!!! This musn't to be\n", 2);
		shell->last_exit_status = ERR_404_EXEC;
	}
	else if (!strcmp("exit", cmd[0]))
		shell->last_exit_status = ft_exit(shell, &(cmd[1]));
	else if (!strcmp("cd", cmd[0]))
		shell->last_exit_status = ft_cd(shell, &(cmd[1]));
	else if (!strcmp("pwd", cmd[0]))
		shell->last_exit_status = ft_pwd();
	else if (!strcmp("export", cmd[0]))
		shell->last_exit_status = ft_export(shell, &(cmd[1]));
	else if (!strcmp("env", cmd[0]))
		shell->last_exit_status = ft_env(shell, &(cmd[1]));
	else if (!strcmp("unset", cmd[0]))
		shell->last_exit_status = ft_unset(shell, &(cmd[1]));
	else
		shell->last_exit_status = ft_exec_prg(shell, cmd);
	return (shell->last_exit_status);
}
