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


