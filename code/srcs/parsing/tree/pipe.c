#include "../../../includes/mini_shell.h"

t_operation	*ft_construct_pipe(t_shell *shell, t_operation *current)
{
	t_operation	*tmp;
	t_operation	*op;
	char		**split;
	size_t		i;

	split = ft_split_str(current->to_parse , "|");
	if (!split)
		return (NULL);
	i = 0;
	op = NULL;
	while (split[i])
	{
		tmp = ft_get_new_node(shell);
		if (!tmp)
		{
			ft_free_2d(split);
			return (NULL);
		}
		tmp->to_parse = split[i++];
		ft_op_add_back(&op, tmp);
	}
	i = 0;
	while (split[i])
		ft_track(split[i++], &(shell->t_pars));
	free(split);
	tmp = op;
	i = 0;
	printf("Debug pipe childs\n");
	while (tmp)
	{
		printf("\t%ld : %s\n", i++, tmp->to_parse);
		tmp = tmp->next;
	}
	return (op);
}
