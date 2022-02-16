
#include "../../../includes/mini_shell.h"

static int	ft_count_var(char *cmd)
{
	size_t	i;
	int		len;

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

static size_t	ft_get_index_var(char *cmd)
{
	size_t	index[3];
	
	index[0] = ft_strichr(cmd, ' ');
	index[1] = ft_strichr(cmd, '$');
	index[2] = ft_strichr(cmd, '\0');
	if (index[0] > index[1])
		index[0] = index[1];
	if (index[0] > index[2])
		index[0] = index[1];
	return (index[0]);
}

static void	ft_catch_var(t_shell *shell, t_quote *quote, char *cmd)
{
	t_env	*node;
	char	*var;
	size_t	i;
	size_t	index;

	i = 0;
	index = ft_get_index_var(cmd);
	var = ft_strndup(cmd, index);
	node = ft_get_env_key(shell->env, var);
	free(var);
	if (!node)
		var = ft_strdup("");
	else
		var = ft_strdup(node->value);
	while (quote->var_env[i])
		i++;
	quote->var_env[i] = var;
}

static char	**ft_get_var_in_tab(t_shell *shell, t_quote *quote, char *cmd)
{
	size_t	i;
	char	*var;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] = '$')
			var = ft_catch_var(shell, quote, cmd + i);
		i++;
	}
}

int	ft_init_quote(t_shell *shell, t_quote *quote, char *cmd)
{
	size_t	i;
	int		len;

	len = ft_count_var(cmd);
	quote->var_env = (char **)malloc(sizeof(char) * (len + 1));
	ft_bzero(quote->var_env, sizeof(char **) * (len + 1));
	ft_get_var_in_tab(quote, cmd);
	ft_track_tab((void **)quote->var_env, &(shell)->t_pars);

}
