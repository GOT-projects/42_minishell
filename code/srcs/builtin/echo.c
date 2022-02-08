#include "../../includes/mini_shell.h"

void	ft_echo(char **args)
{
	_Bool	nl;
	size_t	i;

	i = 0;
	nl = true;
	while (args && args[i++])
		if (i == MY_SIZE_T_MAX)
			exit(EXIT_FAILURE);
	i = 0;
	while (args && args[i] && !ft_strcmp(args[i], "-n"))
	{
		nl = false;
		++i;
	}
	while (args && args[i])
		ft_putstr_fd(args[i++], 1);
	if (nl)
		ft_putstr_fd("\n", 1);
	exit(EXIT_SUCCESS);
}
