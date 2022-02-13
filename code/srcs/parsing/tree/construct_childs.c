#include "../../../includes/mini_shell.h"

t_operation	*ft_get_new_node(t_shell *shell)
{
	t_operation	*op;

	op = ft_track(malloc(sizeof(t_operation)), &(shell->t_pars));
	if (op)
		ft_bzero(op, sizeof(t_operation));
	return (op);
}

t_priority	ft_get_top_priority(char *line)
{
	size_t		i;
	t_priority	priority;
	char		quote;

	i = 0;
	quote = 0;
	priority = CMD;
	while (line[i])
	{
		if (!ft_pars_quote(line[i], &quote) && !quote)
		{
			if (line[i] == '|')
				return (PIPE);
			if (ft_str_start_with(line + i, ">>")
				|| ft_str_start_with(line + i, "<<"))
			{
				priority = REDIRECTION;
				++i;
			}
			else if (ft_str_start_with(line + i, ">")
				|| ft_str_start_with(line + i, "<"))
				priority = REDIRECTION;
		}
		++i;
	}
	return (priority);
}

t_operation	*ft_construct_pipe(t_shell *shell, t_operation *current)
{
	t_operation	*tmp;
	t_operation	*op;
	char		**split;
	size_t		i;

	split = ft_split_str(shell->operation->to_parse , "|");
	if (!split)
		return (NULL);
	i = 0;
	op = NULL;
	while (split[i])
	{
		tmp = ft_get_new_node(shell);
		if (!tmp)
		{
			ft_free2d(split);
			return (NULL);
		}
		tmp->to_parse = split[i++];
		ft_op_add_back(&op, tmp);
	}
	i = 0;
	while (split[i])
		ft_track(split[i++], &(shell->t_pars));
	free(split);
	return (op);
}

int	ft_construct_cmd(t_shell *shell, t_operation *current)
{
	char		**split;

	split = ft_split_str(shell->operation->to_parse , "|");
	if (!split)
		return (1);
	if (!ft_track_tab(split, &(shell->t_pars)))
		return (1);
	return (0);
}

int	ft_construct_child(t_shell *shell, t_operation *current)
{
	t_operation	*node;

	current->genre = ft_get_top_priority(shell->operation->to_parse );
	if (current->genre == PIPE)
	{
		current->childs = ft_construct_pipe(shell, current);
		if (!current->childs)
			return (1);
	}
	else if (current->genre == REDIRECTION)
	{
// check if redirt
	}
	else if (current->genre == CMD)
	{
		if (ft_construct_cmd(shell, current))
			return (1);
	}
	ft_track_free(&(shell->t_pars), current->to_parse);
	current->to_parse = NULL;
	node = current->childs;
	while (node)
	{
		if(ft_construct_child(shell, node))
			return (1);
		node = node->next;
	}
	return (0);
}
