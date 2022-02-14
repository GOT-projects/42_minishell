#include "../../includes/mini_shell.h"

/**
 * @brief print in term the current path
 * 
 * @return int 0 if success, else error
 */
int	ft_pwd(void)
{
	char	path[PATH_MAX];

	errno = 0;
	ft_bzero(path, (PATH_MAX) * sizeof(char));
	if (getcwd(path, PATH_MAX))
	{
		ft_putstr_fd(path, 1);
		ft_putstr_fd("\n", 1);
		return (EXIT_SUCCESS);
	}
	perror("pwd");
	return (errno);
}
