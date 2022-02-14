#include "../../../includes/mini_shell.h"

char	*ft_get_redirect_file(char *str, size_t *offset)
{
	size_t	i;
	size_t	start;
	size_t	end;
	char	quote;

	i = 0;
	quote = 0;
	end = 0;
	while (ft_strchr(SPACES, str[i]))
		++i;
	start = i;
	while (str[i] && !end)
	{
		if (ft_pars_quote(str[i], &quote))
		{
			if (!quote && (!str[i + 1] || ft_strchr(SPACES, str[i + i]) || str[i] == '<' || str[i] == '>'))
				end = i + 1;
		}
		else
		{
			if (!quote && !str[i + 1])
				end = i + 1;
			if (!quote && (ft_strchr(SPACES, str[i]) || str[i] == '<' || str[i] == '>'))
				end = i;
		}
		++i;
	}
	//printf ("%s ! %ld %ld\n", str, start, end);
	if (start >= end)
		return (NULL);
	*offset += end;
	return (ft_strndup(str + start, end - start));
}

t_operation	*ft_get_redirection(t_shell *shell, t_redirection r, char *redir,
	size_t *offset)
{
	t_operation	*new_redir;

	new_redir = ft_get_new_node(shell);
	if (!new_redir)
		return (NULL);
	new_redir->file = ft_get_redirect_file(redir, offset);
	if (!new_redir->file)
	{
		ft_track_free(&(shell->t_pars), new_redir);
		return (NULL);
	}
	//printf("Debug redir: %s\n", new_redir->file);
	ft_track(new_redir->file, &(shell->t_pars));
	new_redir->type_redirection = r;
	new_redir->genre = REDIRECTION;
	return (new_redir);
}

t_operation	*ft_construct_redirection(t_shell *shell, t_operation *current)
{
	size_t	i;
	char	quote;
	t_operation	*op;
	t_operation	*tmp;

	i = 0;
	quote = 0;
	op = NULL;
	while (current->to_parse[i])
	{
		if (!ft_pars_quote(current->to_parse[i], &quote) && !quote)
		{
			if (ft_str_start_with(current->to_parse + i, ">>"))
			{
				tmp = ft_get_redirection(shell, OUT_2, current->to_parse + i
					+ 2, &i);
				if (!tmp)
					return (NULL);
				ft_op_add_back(&op, tmp);
				++i;
			}
			else if (ft_str_start_with(current->to_parse + i, "<<"))
			{
				tmp = ft_get_redirection(shell, IN_2, current->to_parse + i
					+ 2, &i);
				if (!tmp)
					return (NULL);
				
				ft_op_add_back(&op, tmp);
				++i;
			}
			else if (ft_str_start_with(current->to_parse + i, ">"))
			{
				tmp = ft_get_redirection(shell, OUT_1, current->to_parse + i
					+ 1, &i);
				if (!tmp)
					return (NULL);
				ft_op_add_back(&op, tmp);
			}
			else if (ft_str_start_with(current->to_parse + i, "<"))
			{
				tmp = ft_get_redirection(shell, IN_1, current->to_parse + i
					+ 1, &i);
				if (!tmp)
					return (NULL);
				ft_op_add_back(&op, tmp);
			}
		}
		++i;
	}
	tmp = op;
	i = 0;
	printf("Debug redirection de %s\n", current->to_parse);
	while (tmp)
	{
		printf("\t%ld : %s\n", i++, tmp->file);
		tmp = tmp->next;
	}
	return (op);
}
