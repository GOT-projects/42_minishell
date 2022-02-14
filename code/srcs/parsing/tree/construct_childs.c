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
	while (line && line[i])
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

int	ft_construct_child(t_shell *shell, t_operation *current)
{
	t_operation	*node;

	current->genre = ft_get_top_priority(current->to_parse);
	printf("yolo %d, %d\n", current->genre, REDIRECTION);
	if (current->genre == PIPE)
	{
		current->childs = ft_construct_pipe(shell, current);
		if (!current->childs)
			return (1);
	}
	else if (current->genre == REDIRECTION)
	{
		current->lst_redir = ft_construct_redirection(shell, current);
		if (!current->lst_redir)
			return (1);
		// childs
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
