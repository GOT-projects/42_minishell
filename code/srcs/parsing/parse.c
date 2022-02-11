#include "../../includes/mini_shell.h"

/**
 * @brief check if the quotes are finish (open and not close)
 * 
 * @param line the command line
 * @return _Bool true if ok, false else
 *//*
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
*/
/**
 * @brief check if the pipes are ok
 * 
 * @param line the command line
 * @return _Bool true if ok, false else
 *//*
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
			else if (pipe && !ft_strchr("| &", (int)line[i])) //change
				pipe = 0;
			else if (pipe)
				return (false);
		}
		++i;
	}
	return (true);
}

char	*ft_strchrstr(char *str, char *to_find)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i + j] && to_find[j] && str[i + j] == to_find[j])
			++j;
		if (to_find[j] == 0)
			return (str + i);
	}
	return (NULL);
}
*/

/*
int main(int argc, char const *argv[])
{
	char *test;
	while (1)
	{
		test = readline("> ");
		printf("%s\n", test);
		ft_check_syntaxe(test);
		add_history(test);
		free(test);
	}
	return 0;
}
*/