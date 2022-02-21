/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges & jmilhas <x@student.42lyon.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 20:44:37 by aartiges &        #+#    #+#             */
/*   Updated: 2022/02/21 20:44:39 by aartiges &       ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mini_shell.h"

/**
 * @brief add a child node if not exist to the current/redirection node
 * add to the current child->to_parse the substring done by pos
 * 
 * @param shell the shell
 * @param current the current node (genre redirection)
 * @param limits array {start, end} the indexs of the substring to add at the
 * to_parse of the child
 * @return int 0 if success, 1 if error
 */
static int	ft_redirection_add_child(t_shell *shell, t_node *current,
	size_t limits[2])
{
	char	*tmp;
	char	*ret;

	if (limits[0] >= limits[1])
		return (0);
	if (!(current->childs))
	{
		current->childs = ft_get_new_node(shell);
		if (!(current->childs))
			return (1);
	}
	tmp = ft_strndup(current->to_parse + limits[0], limits[1] - limits[0]);
	if (!tmp)
		return (1);
	ret = ft_strjoin(current->childs->to_parse, tmp);
	free(tmp);
	if (!ret)
		return (1);
	if (current->childs->to_parse)
		ft_track_free(&(shell->t_pars), current->childs->to_parse);
	current->childs->to_parse = ft_track(ret, &(shell->t_pars));
	return (0);
}

/**
 * @brief get the name of file after a redirection in the command line
 * (>filename)
 * /!\ function with side effect /!\
 * 
 * @param str the command line
 * @param i a pointer on the index where we start to search the filename
 * @return char* the filename
 */
static char	*ft_get_redirect_file(char *str, size_t *i)
{
	size_t	limit[2];
	char	quote;

	while (ft_strchr(SPACES, str[*i]))
		++(*i);
	quote = 0;
	limit[0] = *i;
	limit[1] = 0;
	while (str[*i] && !limit[1])
	{
		ft_pars_quote(str[*i], &quote);
		if (!quote)
		{
			if (str[*i] == '<' || str[*i] == '>' || ft_strchr(SPACES, str[*i]))
				limit[1] = *i;
			else if (!str[*i + 1])
				limit[1] = ++(*i);
		}
		if (!limit[1])
			++(*i);
	}
	if (limit[0] >= limit[1])
		return (NULL);
	return (ft_strndup(str + limit[0], limit[1] - limit[0]));
}

/**
 * @brief /!\ function with side effect /!\
 * create a redirection to add at the list of redirection
 * 
 * @param shell the shell
 * @param r the type of the redirection
 * @param current the current node of the redirection
 * @param i a pointer on the index where we start to apply what we need to do
 * @return t_node* NULL if error, the redirection to add to the list of
 * redirection if success
 */
static t_node	*ft_create_redir(t_shell *shell, t_redirection	r,
	t_node *current, size_t *i)
{
	t_node	*tmp;

	tmp = ft_get_new_node(shell);
	if (!tmp)
		return (NULL);
	if (r == OUT_2 || r == IN_2)
		(*i) += 2;
	else if (r == OUT_1 || r == IN_1)
		++(*i);
	tmp->file = ft_get_redirect_file(current->to_parse, i);
	if (!tmp->file)
	{
		ft_track_free(&(shell->t_pars), tmp);
		return (NULL);
	}
	ft_track(tmp->file, &(shell->t_pars));
	tmp->type_redirection = r;
	return (tmp);
}

/**
 * @brief /!\ function with side effect /!\
 * add a redirection at the list of redirection
 * 
 * @param shell the shell
 * @param current the current node of genre redirection
 * @param i a pointer on the index where we start to apply what we need to do
 * @return int 0 if success, 1 else
 */
static int	ft_redirection_add_redir(t_shell *shell, t_node *current, size_t *i)
{
	t_redirection	r;
	t_node			*tmp;

	if (ft_str_start_with(current->to_parse + *i, ">>"))
		r = OUT_2;
	else if (ft_str_start_with(current->to_parse + *i, "<<"))
		r = IN_2;
	else if (ft_str_start_with(current->to_parse + *i, ">"))
		r = OUT_1;
	else if (ft_str_start_with(current->to_parse + *i, "<"))
		r = IN_1;
	else
		return (1);
	tmp = ft_create_redir(shell, r, current, i);
	if (!tmp || (r == IN_2 && ft_get_heredoc(shell, tmp)))
		return (1);
	ft_op_add_back(&(current->lst_redir), tmp);
	return (0);
}

/**
 * @brief construct node redirection
 * 
 * @param shell the shell
 * @param current the current node in the tree
 * @return int 0 if success, 1 else
 */
int	ft_construct_redirection(t_shell *shell, t_node *current)
{
	size_t	i;
	size_t	pos[2];
	char	quote;

	i = 0;
	quote = 0;
	ft_bzero(pos, 2 * sizeof(size_t));
	while (current->to_parse[i])
	{
		if (!ft_pars_quote(current->to_parse[i], &quote) && !quote
			&& (current->to_parse[i] == '>' || current->to_parse[i] == '<'))
		{
			pos[1] = i;
			if (ft_redirection_add_child(shell, current, pos))
				return (1);
			if (ft_redirection_add_redir(shell, current, &i))
				return (1);
			pos[0] = i;
		}
		else
			++i;
	}
	pos[1] = i;
	return (ft_redirection_add_child(shell, current, pos));
}
