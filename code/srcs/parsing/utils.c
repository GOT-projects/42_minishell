#include "../../includes/mini_shell.h"

_Bool	ft_str_start_with(char *str, char *to_find)
{
	size_t	j;

	j = 0;
	while (str[j] && to_find[j] && str[j] == to_find[j])
		++j;
	if (to_find[j] == 0)
		return (true);
	return (false);
}

int	ft_pars_quote(char c, char *quote)
{
	if (!(*quote) && (c == '"' || c == '\"'))
	{
		(*quote) = c;
		return (1);
	}
	else if ((*quote) == c)
	{
		(*quote) = 0;
		return (1);
	}
	return (0);
}

void	ft_free_2d(char **array)
{
	size_t	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}
