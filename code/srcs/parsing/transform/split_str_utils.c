#include "../../../includes/mini_shell.h"

char	*create_string(char *str, size_t start, size_t end)
{
	size_t	i;
	char	*ret;

	ret = malloc(sizeof(char) * (end - start + 1));
	if (!ret)
		return (NULL);
	i = start;
	while (i < end)
	{
		ret[i - start] = str[i];
		i++;
	}
	ret[end - start] = '\0';
	return (ret);
}

int	ft_free2d_index(char **split, size_t index)
{
	size_t	i;

	i = 0;
	while (i <= index)
		free(split[i]);
	free(split);
	return (1);
}
