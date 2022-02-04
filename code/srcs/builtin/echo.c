#include "../../includes/mini_shell.h"

void	ft_echo(char **args)
{
	_Bool	nl;
	size_t	i;

	i = 0;
	nl = true;
	while (args && args[i] && !ft_strcmp(args[i], "-n"))
	{
		nl = false;
		++i;
	}
	while (args && args[i])
		ft_putstr_fd(args[i++], 1);
	if (nl)
		write(1, "\n", 1);
	exit(EXIT_SUCCESS);
}