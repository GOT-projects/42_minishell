#include "../../includes/mini_shell.h"

/**
 * @brief check if the quotes are finish (open and not close)
 * 
 * @param line the command line
 * @return _Bool true if ok, false else
 */
_Bool	ft_check_quotes(char *line)
{
	size_t	i;
	char	tmp;

	tmp = 0;
	i = 0;
	while (line[i])
	{
		if (!tmp && line[i] == '"' || line[i] == '\"')
			tmp = line[i];
		else if (tmp && line[i] == tmp)
			tmp = 0;
		++i;
	}
	if (!tmp)
		return (true);
	return (false);
}

_Bool	ft_check_pipe(char *line)
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
			if (pipe < 1 && line[i] == '|')
				++pipe;
			else if (pipe && line[i] != '|')
				pipe = 0;
			if (pipe > 1)
				return (false);
		}
		else
			pipe = 0;
		++i;
	}
	return (true);
}

/**
 * @brief check if the pipes are ok
 * 
 * @param line the command line
 * @return _Bool true if ok, false else
 */
_Bool	ft_check_pipes(char *line)
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
			if (!pipe && line[i] == '|')
				pipe = 1;
			else if (pipe && !strchr("| &", (int)line[i])) //change
				pipe = 0;
			else if (pipe)
				return (false);
		}
		++i;
	}
	return (true);
}

_Bool	ft_check_syntaxe(char *line)
{
	size_t	i;
	char	cmd;
	char	separator;

	cmd = 0;
	separator = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] != ' ')
		if (strchr("|", line[i]))
			separator = line[i];
	}
}