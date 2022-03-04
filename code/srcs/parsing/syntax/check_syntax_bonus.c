/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges <aartiges@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 23:04:21 by aartiges          #+#    #+#             */
/*   Updated: 2022/03/02 23:06:18 by aartiges         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mini_shell.h"

/**
 * @brief check if an error of syntaxe occurs on
 * 
 * @param line the command line at the index i
 * @param state the state of the check of the syntax
 * @return int CHECK_OK if success, else error
 */
static int	ft_check_syntax_algo_no_quote(char *line, int *state)
{
	if ((*state & (CHECK_SEPARATOR)) && ft_str_start_with(line, "&&"))
		return (CHECK_AND);
	else if ((*state & (CHECK_SEPARATOR)) && ft_str_start_with(line, "||"))
		return (CHECK_OR);
	else if ((*state & (CHECK_SEPARATOR)) && ft_str_start_with(line, "|"))
		return (CHECK_PIPE);
	else if ((*state & (CHECK_REDIRECTION)) && ft_str_start_with(line, ">>"))
		return (CHECK_RED_APPEND);
	else if ((*state & (CHECK_REDIRECTION)) && ft_str_start_with(line, ">"))
		return (CHECK_RED_CREATE);
	else if ((*state & (CHECK_REDIRECTION)) && ft_str_start_with(line, "<<"))
		return (CHECK_RED_HR_DOC);
	else if ((*state & (CHECK_REDIRECTION)) && ft_str_start_with(line, "<"))
		return (CHECK_RED_INPUT);
	else if (ft_str_start_with(line, "(") && (*state & (CHECK_SEPARATOR2)))
		return (CHECK_SUB_OPEN);
	else if (ft_str_start_with(line, ")") && (*state & (CHECK_SEPARATOR)))
		return (CHECK_SUB_CLOSE);
	return (CHECK_OK);
}

/**
 * @brief if no error occurs with ft_check_syntax_algo_no_quote()
 * that function will refresh the state of the command line
 * 
 * @param line the command line
 * @param state the state of the check syntax
 * @param i the index of the line
 * @return int 1 if the state have change
 */
static int	ft_check_syntax_apply_algo(char *line, int *state, size_t *i)
{
	int	old;

	old = *state;
	if (ft_str_start_with(line + *i, "&&"))
		*state = CHECK_AND;
	else if (ft_str_start_with(line + *i, "||"))
		*state = CHECK_OR;
	else if (ft_str_start_with(line + *i, "|"))
		*state = CHECK_PIPE;
	else if (ft_str_start_with(line + *i, ">>"))
		*state = CHECK_RED_APPEND;
	else if (ft_str_start_with(line + *i, ">"))
		*state = CHECK_RED_CREATE;
	else if (ft_str_start_with(line + *i, "<<"))
		*state = CHECK_RED_HR_DOC;
	else if (ft_str_start_with(line + *i, "<"))
		*state = CHECK_RED_INPUT;
	else if (ft_str_start_with(line + *i, "("))
		*state = CHECK_SUB_OPEN;
	else if (ft_str_start_with(line + *i, ")"))
		*state = CHECK_SUB_CLOSE;
	else if (line[*i] != ' ')
		*state = CHECK_TEXT;
	return (old != *state);
}

/**
 * @brief The algo apply on each index of the command line
 * 
 * @param line the command line
 * @param i the current index of work on the command line
 * @param state the state of the check of the command line
 * @param quote quote = ''' or '"' if the check is currently between 2 quotes,
 * 0 else
 * @return int the error code of the syntax, CHECK_OK else
 */
static int	ft_check_syntax_algo_with_quote(char *line, size_t *i, int *state,
			char *quote)
{
	if (!(*quote) && (line[*i] == '"' || line[*i] == '\''))
	{
		(*quote) = line[*i];
		*state = CHECK_TEXT;
	}
	else if ((*quote) && (*quote) == line[*i])
		(*quote) = 0;
	else if (!(*quote))
	{
		if (ft_check_syntax_algo_no_quote(line + *i, state) != CHECK_OK)
			return (ft_check_syntax_algo_no_quote(line + *i, state));
		if (ft_check_syntax_apply_algo(line, state, i) && *state
			& (CHECK_AND | CHECK_OR | CHECK_RED_APPEND | CHECK_RED_HR_DOC))
			++(*i);
	}
	else if (line[*i] != ' ')
		*state = CHECK_TEXT;
	++(*i);
	return (CHECK_OK);
}

/**
 * @brief Apply the algo ft_check_syntaxe_algo_with_quote on each index of the
 * command line
 * 
 * @param line the command line
 * @return int the error code of the syntax, CHECK_OK else
 */
static int	ft_check_syntax_algo(char *line)
{
	size_t	i;
	int		state;
	char	quote;
	int		ret;

	state = EMPTY;
	quote = 0;
	i = 0;
	if (!ft_check_parenthese_post_pars(line))
		return (CHECK_SUB_CLOSE);
	while (line[i])
	{
		ret = ft_check_syntax_algo_with_quote(line, &i, &state, &quote);
		if (ret != CHECK_OK)
			return (ret);
	}
	if (quote)
		return (CHECK_QUOTE);
	if (state & (CHECK_TEXT | CHECK_SUB_CLOSE))
		return (CHECK_OK);
	return (state);
}

/**
 * @brief check if the command line have a good syntax and print an error
 * message if the line have an error syntax
 * 
 * @param line the command line
 * @return int 1 if error, 0 else
 */
int	ft_check_syntax(char *line)
{
	int	state;

	state = ft_check_syntax_algo(line);
	if (state == EMPTY)
		ft_putstr_fd("Syntax error: empty\n", 2);
	else if (state == CHECK_PIPE)
		ft_putstr_fd("Syntax error: near '|'\n", 2);
	else if (state == CHECK_RED_APPEND)
		ft_putstr_fd("Syntax error: near '>>'\n", 2);
	else if (state == CHECK_RED_CREATE)
		ft_putstr_fd("Syntax error: near '>'\n", 2);
	else if (state == CHECK_RED_HR_DOC)
		ft_putstr_fd("Syntax error: near '<<'\n", 2);
	else if (state == CHECK_RED_INPUT)
		ft_putstr_fd("Syntax error: near '<'\n", 2);
	else if (state == CHECK_QUOTE)
		ft_putstr_fd("Syntax error: quotes\n", 2);
	else
		ft_syntax_error_bonus(state);
	return (state != CHECK_OK);
}
