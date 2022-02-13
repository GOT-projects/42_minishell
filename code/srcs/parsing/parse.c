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

//ft_track_tab
//ft_track

int	ft_parse(t_shell *shell, char *line)
{
	shell->operation = ft_track(malloc(sizeof(t_operation)), &(shell->t_pars));
	if (!shell->operation)
		return (1);
	ft_bzero(shell->operation, sizeof(t_operation));
	shell->operation->root = true;
	shell->operation->to_parse = ft_track(ft_strtrim(line, SPACES),
		&(shell->t_pars));
	if (shell->operation->to_parse[ft_strlen(shell->operation->to_parse) - 1]
			== '|' && (ft_get_forgot_pipe(shell)
			|| ft_check_syntax(shell->operation->to_parse)))
		return (1);
	printf("Debugfin parse %d\n", shell->last_exit_status);
	return (0);
}