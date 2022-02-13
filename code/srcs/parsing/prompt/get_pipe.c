#include "../../../includes/mini_shell.h"

_Bool	ft_is_empty(char *str)
{
	size_t	i;

	if (!str)
		return (true);
	i = 0;
	while (str[i])
	{
		if (!ft_strchr(SPACES, str[i]))
			return (false);
		++i;
	}
	return (true);
}

int	ft_get_forgot_pipe(t_shell *shell)
{
	char	*forgot_pipe;
	char	*new_cmd;

	forgot_pipe = readline("pipe > ");
	while (forgot_pipe && ft_is_empty(forgot_pipe))
	{
		free(forgot_pipe);
		forgot_pipe = readline("pipe > ");
	}
	if (forgot_pipe)
	{
		new_cmd = ft_strjoin(shell->operation->to_parse, forgot_pipe);
		free(forgot_pipe);
		ft_track_free(&(shell->t_pars), shell->operation->to_parse);
		if (!new_cmd)
			return (1);
		shell->operation->to_parse = new_cmd;
		ft_track(shell->operation->to_parse, &(shell->t_pars));
	}
	return (0);
}
