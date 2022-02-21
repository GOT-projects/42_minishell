/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges & jmilhas <x@student.42lyon.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 20:41:09 by aartiges &        #+#    #+#             */
/*   Updated: 2022/02/21 20:41:15 by aartiges &       ###   ########lyon.fr   */
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
static int	ft_check_syntax_algo_no_quote(char *line, char *state)
{
	char	test;

	if (*state != CHECK_TEXT && ft_str_start_with(line, "|"))
		return (CHECK_PIPE);
	else
	{
		test = (*state & (CHECK_RED_APPEND | CHECK_RED_CREATE | CHECK_RED_HR_DOC
					| CHECK_RED_INPUT));
		if (test)
		{
			if (ft_str_start_with(line, ">>"))
				return (CHECK_RED_APPEND);
			else if (ft_str_start_with(line, ">"))
				return (CHECK_RED_CREATE);
			else if (ft_str_start_with(line, "<<"))
				return (CHECK_RED_HR_DOC);
			else if (ft_str_start_with(line, "<"))
				return (CHECK_RED_INPUT);
		}
	}
	return (CHECK_OK);
}

/**
 * @brief if no error occurs with ft_check_syntax_algo_no_quote()
 * that function will refresh the state of the command line
 * 
 * @param line the command line
 * @param state the state of the check syntax
 * @param i the index of the line
 */
static void	ft_check_syntax_apply_algo(char *line, char *state, size_t *i)
{
	if (ft_str_start_with(line + *i, "|"))
		*state = CHECK_PIPE;
	else if (ft_str_start_with(line + *i, ">>"))
	{
		*state = CHECK_RED_APPEND;
		++(*i);
	}
	else if (ft_str_start_with(line + *i, ">"))
		*state = CHECK_RED_CREATE;
	else if (ft_str_start_with(line + *i, "<<"))
	{
		*state = CHECK_RED_HR_DOC;
		++(*i);
	}
	else if (ft_str_start_with(line + *i, "<"))
		*state = CHECK_RED_INPUT;
	else if (line[*i] != ' ')
		*state = CHECK_TEXT;
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
static int	ft_check_syntax_algo_with_quote(char *line, size_t *i, char *state,
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
		ft_check_syntax_apply_algo(line, state, i);
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
	char	state;
	char	quote;
	int		ret;

	state = EMPTY;
	quote = 0;
	i = 0;
	while (line[i])
	{
		ret = ft_check_syntax_algo_with_quote(line, &i, &state, &quote);
		if (ret != CHECK_OK)
			return (ret);
	}
	if (quote)
		return (CHECK_QUOTE);
	if (state & CHECK_TEXT)
		return (CHECK_OK);
	return (state);
}

/**
 * @brief check if the command line have a good syntax and print an error
 * message if the line have an error syntax (total command)
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
	if (state & (EMPTY | CHECK_PIPE | CHECK_RED_APPEND | CHECK_RED_CREATE
			| CHECK_RED_HR_DOC | CHECK_RED_INPUT | CHECK_QUOTE))
		return (1);
	return (0);
}
