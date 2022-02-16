#include "../../../includes/mini_shell.h"

/**
 * @brief add at the back of the list
 * 
 * @param ops a pointer on the pointer on the 1st element of the list
 * @param node the new element
 */
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

size_t	ft_op_bro_size(t_operation *childs)
{
	size_t	i;

	i = 0;
	while (childs)
	{
		++i;
		childs = childs->next;
	}
	return (i);
}
