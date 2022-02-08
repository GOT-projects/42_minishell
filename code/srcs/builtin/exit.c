#include "../../includes/mini_shell.h"

_Bool	ft_is_numeric_str(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		if (!ft_isdigit(str[i++]))
			return (false);
	return (true);
}

void	ft_free_minishell(t_shell *shell)
{
	if (shell)
	{
		// TO_ADD_ALL_TRACKS
		ft_track_free_all(&(shell->t_env));
	}
}

/**
 * @brief function thatexit the current process with the status given
 * 
 * @param shell if set, the function will free the environnement of the
 * minishell
 * @param status exit code of the process
 * @return ** void
 */
int	ft_exit(t_shell *shell, char **status)
{
	size_t	size;

	size = 0;
	while (status[size])
		++size;
	if (size > 0 && !ft_is_numeric_str(status[0]))
	{
		ft_putstr_fd("exit: numeric argument required\n", 2);
		ft_free_minishell(shell);
		exit(255);
	}
	if (size > 1)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		shell->last_exit_status = 1;
		return (1);
	}
	ft_putstr_fd("exit\n", 1);
	ft_free_minishell(shell);
	if (!size)
		exit(shell->last_exit_status);
	exit(ft_atoi(status[0]));
}
