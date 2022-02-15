#include "../../../includes/mini_shell.h"

/**
 * @brief check if a string can be a shell var
 * 
 * @param var the string
 * @return _Bool true if it can be a shell var, false else
 */
_Bool	ft_is_shell_var(char const *var)
{
	size_t	i;

	i = 0;
	while (var[i] && i < MY_SIZE_T_MAX)
	{
		if (i == 0 && !(ft_isalpha((int)var[i]) || var[i] == '_'))
			return (false);
		if (!(ft_isalnum((int)var[i]) || var[i] == '_'))
			return (false);
		++i;
	}
	if (var[i] && i == MY_SIZE_T_MAX)
		return (false);
	return (true);
}
