#include "../../includes/mini_shell.h"

/**
 * @brief print errors if the research of the executable not match
 * 
 * @param cmd arguments array of the command (like "ls" "-l" "/")
 * @param error_research the error of the research (future exit status)
 */
void	ft_prg_error_research_path(char **cmd, int error_research)
{
	if (error_research == ERR_403_EXEC || error_research == ERR_404_EXEC)
	{
		ft_putstr_fd(cmd[0], 2);
		if (error_research == ERR_403_EXEC)
			ft_putstr_fd(": Permission denied\n", 2);
		if (strchr(cmd[0], '/') && error_research == ERR_404_EXEC)
			ft_putstr_fd(": No such file or directory\n", 2);
		else if (strchr(cmd[0], '/') && error_research == ERR_403_EXEC)
			ft_putstr_fd(": Command not found\n", 2);
	}
	else
		perror(cmd[0]);
}

/**
 * @brief print the error on signal and return the good exit status
 * 
 * @param prg_name the program name
 * @param status the status of the child process
 * @return int -- 
 */
int	ft_error_exit_process(char *prg_name, int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		ft_putstr_fd(prg_name, 2);
		ft_putstr_fd(": process terminated due to receipt of signal ", 2);
		ft_putnbr_fd(WTERMSIG(status), 2);
		ft_putstr_fd("\n", 2);
	}
	return (1);
}
