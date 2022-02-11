#include "../../includes/mini_shell.h"

_Bool	ft_check_pipe_or(char *line)
{
	size_t	i;
	char	quote;
	int		pipe;

	pipe = 0;
	quote = 0;
	i = 0;
	while (line[i])
	{
		if (quote && line[i] == quote)
			quote = 0;
		else if (!quote && line[i] == '"' || line[i] == '\"')
			quote = line[i];
		if (!quote)
		{
			if (pipe < 2 && line[i] == '|')
				++pipe;
			else if (pipe && line[i] != '|')
				pipe = 0;
			if (pipe > 2)
				return (false);
		}
		else
			pipe = 0;
		++i;
	}
	return (true);
}


/**
 * @brief check if all parentheses open are close
 * 
 * @param line the command line
 * @return _Bool true if ok, false else
 */
_Bool	ft_check_parenthese(char *line)
{
	size_t	i;
	char	quote;
	int		tmp;

	tmp = 0;
	quote = 0;
	i = 0;
	while (line[i] && tmp >= 0)
	{
		if (quote && line[i] == quote)
			quote = 0;
		else if (!quote && line[i] == '"' || line[i] == '\"')
			quote = line[i];
		if (!quote)
		{
			if (line[i] == '(')
				++tmp;
			else if (line[i] == ')')
				--tmp;
		}
		++i;
	}
	if (!quote && !tmp)
		return (true);
	return (false);
}

_Bool	ft_check_parenthese_open(char *line)
{
	
}
