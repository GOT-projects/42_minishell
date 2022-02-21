#include "../../../includes/mini_shell.h"

int	ft_c_quote(int c)
{
	if (c == DOUBLE_QUOTE || c == SIMPLE_QUOTE)
		return (1);
	return (0);
}

int	ft_get_len_var(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == ' ' || cmd[i] == '$')
			return (i);
		else if (cmd[i] == DOUBLE_QUOTE || cmd[i] == SIMPLE_QUOTE)
			return (i);
		i++;
	}
	return (i);
}

int	ft_get_full_len_var(t_shell *shell, t_var *var)
{
	char	*value;
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (var->t_var[i])
	{
		value = ft_get_env_val(ft_get_env_key(shell->env, var->t_var[i]));
		len += ft_strlen(value);
		i++;
	}
	return (len);
}

int	ft_get_nb_var(char *cmd)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (cmd[i])
	{
		if (cmd[i] == '$')
			len++;
		i++;
	}
	return (len);
}


