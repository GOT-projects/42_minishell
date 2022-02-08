#include "../../includes/mini_shell.h"

int	ft_exec_prg(t_shell *shell, char **cmd)
{
	pid_t	pid;
	
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
