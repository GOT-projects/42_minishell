#include "includes/mini_shell.h"

char	*ft_get_redirect_file(char *str, size_t *offset)
{
	size_t	i;
	size_t	limit[2];
	int		change_quote;
	char	quote;

	i = 0;
	while (ft_strchr(SPACES, str[i]))
		++i;
	quote = 0;
	limit[0] = i;
	limit[1] = 0;
	while (str[i] && !limit[1])
	{
		change_quote = ft_pars_quote(str[i], &quote);
		if (!quote)
		{
			if ((change_quote && (!str[i + 1] || ft_strchr(SPACES, str[i + i])
						|| str[i] == '<' || str[i] == '>')) || (!change_quote
					&& !str[i + 1]))
				limit[1] = i + 1;
			if (!change_quote && (ft_strchr(SPACES, str[i]) || str[i] == '<'
					|| str[i] == '>'))
				limit[1] = i;
		}
		++i;
	}
	if (limit[0] >= limit[1])
		return (NULL);
	*offset += limit[1];
	return (ft_strndup(str + limit[0], limit[1] - limit[0]));
}

t_node	*ft_get_redirection(t_shell *shell, t_redirection r, char *redir,
	size_t *offset)
{
	t_node	*new_redir;

	new_redir = ft_get_new_node(shell);
	if (!new_redir)
		return (NULL);
	new_redir->file = ft_get_redirect_file(redir, offset);
	if (!new_redir->file)
	{
		ft_track_free(&(shell->t_pars), new_redir);
		return (NULL);
	}
	ft_track(new_redir->file, &(shell->t_pars));
	new_redir->type_redirection = r;
	new_redir->genre = REDIRECTION;
	return (new_redir);
}

char	*ft_strjoin_free_1_index_2(char *s1, char *s2, size_t size_2)
{
	char	*tmp;
	char	*ret;

	if (size_2 == 0)
		return (s1);
	tmp = ft_strndup(s2, size_2);
	if (!tmp)
		return (NULL);
	ret = ft_strjoin(s1, tmp);
	free(tmp);
	if (!ret)
		return(NULL);
	free(s1);
	return (ret);
}

t_node	*ft_construct_redirection(t_shell *shell, t_node *current)
{
	size_t	i;
	size_t	pos[2];
	char	quote;
	t_node	*op;
	t_node	*tmp;

	i = 0;
	ft_bzero(pos, 2 * sizeof(size_t));
	quote = 0;
	op = NULL;
	while (current->to_parse[i])
	{
		if (!ft_pars_quote(current->to_parse[i], &quote) && !quote)
		{
			if (ft_str_start_with(current->to_parse + i, ">>"))
			{
				pos[1] = i;
				if (pos[0] < pos[1])
					write(1, current->to_parse + pos[0], pos[1] - pos[0]);
				printf("\n");
				tmp = ft_get_redirection(shell, OUT_2, current->to_parse + i
					+ 2, &i);
				if (!tmp)
					return (NULL);
				ft_op_add_back(&op, tmp);
				pos[0] = i + 2;
				++i;
			}
			else if (ft_str_start_with(current->to_parse + i, "<<"))
			{
				pos[1] = i;
				if (pos[0] < pos[1])
					write(1, current->to_parse + pos[0], pos[1] - pos[0]);
				printf("\n");
				tmp = ft_get_redirection(shell, IN_2, current->to_parse + i
					+ 2, &i);
				if (!tmp)
					return (NULL);
				
				ft_op_add_back(&op, tmp);
				pos[0] = i + 2;
				++i;
			}
			else if (ft_str_start_with(current->to_parse + i, ">"))
			{
				pos[1] = i;
				if (pos[0] < pos[1])
					write(1, current->to_parse + pos[0], pos[1] - pos[0]);
				printf("\n");
				tmp = ft_get_redirection(shell, OUT_1, current->to_parse + i
					+ 1, &i);
				if (!tmp)
					return (NULL);
				ft_op_add_back(&op, tmp);
				pos[0] = i + 1;
			}
			else if (ft_str_start_with(current->to_parse + i, "<"))
			{
				pos[1] = i;
				if (pos[0] < pos[1])
					write(1, current->to_parse + pos[0], pos[1] - pos[0]);
				printf("\n");
				tmp = ft_get_redirection(shell, IN_1, current->to_parse + i
					+ 1, &i);
				if (!tmp)
					return (NULL);
				ft_op_add_back(&op, tmp);
				pos[0] = i + 1;
			}
		}
		++i;
	}
	if (pos[0] < i)
		write(1, current->to_parse + pos[0], i - pos[0]);
	printf("\n");
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
