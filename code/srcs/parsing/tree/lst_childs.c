#include "../../../includes/mini_shell.h"

void	ft_op_add_back(t_operation **ops, t_operation *node)
{
	t_operation	*tmp;
	if (*ops == NULL)
		*ops = node;
	else
	{
		tmp = *ops;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
}
