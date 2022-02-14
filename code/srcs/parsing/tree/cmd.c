#include "../../../includes/mini_shell.h"

int	ft_construct_cmd(t_shell *shell, t_operation *current)
{
	char		**split;

	split = ft_split_str(current->to_parse, " ");
	if (!split)
		return (1);
	if (!ft_track_tab((void **)split, &(shell->t_pars)))
		return (1);
	current->cmd = split;
	printf("debug cmd\n");
	int i = 0;
	while (current->cmd[i])
		{printf("\t%d : %s\n", i, current->cmd[i]);++i;}
	return (0);
}
