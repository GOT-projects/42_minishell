#include "../../includes/mini_shell.h"

/**
 * @brief function thatexit the current process with the status given
 * 
 * @param shell if set, the function will free the environnement of the
 * minishell
 * @param status exit code of the process
 * @return ** void
 */
void	ft_exit(t_shell *shell, int status)
{
	if (shell)
	{
		/* ft_track_free_all(shell->t_pars); */
		ft_track_free_all(shell->t_env);
	}
	ft_putstr_fd("exit\n", 1);
	exit(status);
}
