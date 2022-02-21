
#include "../../../includes/mini_shell.h"

int	ft_c_quote(int c)
{
	if (c == DOUBLE_QUOTE || c == SIMPLE_QUOTE)
		return (1);
	return (0);
}
