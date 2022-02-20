#include "../../../includes/mini_shell.h"

void	ft_tolower_str(char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
	{
		str[i] = ft_tolower(str[i]);
		++i;
	}
}

/**
 * @brief split the command (prepare for execve)
 * 
 * @param shell the shell
 * @param current the current node of the tree
 * @return int 0 if success, 1 else
 */
int	ft_construct_cmd(t_shell *shell, t_operation *current)
{
	char		**split;

	split = ft_split_str(current->to_parse, " ");
	if (!split)
		return (1);
	if (!ft_track_tab((void **)split, &(shell->t_pars)))
		return (1);
	if (!strchr(split[0], '/'))
		ft_tolower_str(split[0]);
	current->cmd = split;
	return (0);
}
