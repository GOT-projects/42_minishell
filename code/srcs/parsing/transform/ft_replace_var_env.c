
#include "../../../includes/mini_shell.h"

static int	ft_get_len_var(char *cmd)
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

static int	ft_get_full_len_var(t_shell *shell, t_var *var)
{
	char	*value;
	int	i;
	int	len;

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

static int	ft_get_nb_var(char *cmd)
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

static char	**ft_get_var_in_tab(t_var *var, char *cmd)
{
	int	i;
	int	j;
	int	index;
	int	state;

	i = 0;
	j = 0;
	state = 0;
	index = 0;
	while (cmd[i])
	{
		if (!state && (cmd[i] == SIMPLE_QUOTE || cmd[i] == DOUBLE_QUOTE))
			state = cmd[i];
		else if (state && cmd[i] == state)
			state = 0;
		if (cmd[i] == '$')
		{
			index = ft_get_len_var(cmd + i + 1);
			var->t_var[j] = ft_strndup(cmd + i + 1, index);
			j++;
		}
		i++;
	}
	var->t_var[j] = NULL;
	return (var->t_var);
}

static void	ft_check_quote(t_var *var, char *cmd)
{
	int	i;
	int	j;
	int		state;

	i = 0;
	j = 0;
	state = 0;
	while (cmd[i])
	{
		if ((cmd[i] == DOUBLE_QUOTE || cmd[i] == SIMPLE_QUOTE) && !state)
			state = cmd[i];
		else if ((cmd[i] == DOUBLE_QUOTE || cmd[i] == SIMPLE_QUOTE) && state == cmd[i])
			state = 0;
		else if ((!state || state == DOUBLE_QUOTE) && cmd[i] == '$')
			var->p_bool[j++] = 1;
		else if (state == SIMPLE_QUOTE && cmd[i] == '$')
			var->p_bool[j++] = 0;
		i++;
	}
}
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

static void	ft_completed_var_in_cmd(t_shell *shell, t_var *var, char *cmd, int **st)
{
	int	i;
	int	j;
	int	k;
	char	*tmp;

	i = -1;
	j = 0;
	k = 0;
	while (cmd[++i])
	{
		while (var->n_cmd[k])
			k++;
		if (var->p_bool[j] && cmd[i] == '$' && ft_is_shell_var(var->t_var[j]))
		{
			tmp = ft_get_env_val(ft_get_env_key(shell->env, var->t_var[j]));
			if (tmp)
			{
				var->n_cmd = ft_strcat(var->n_cmd, tmp);
				st[j][0] = k;
				st[j][1] = ft_strlen(var->t_var[j]) + k;
				i += ft_strlen(var->t_var[j]);
				j++;
			}
			else
			{
				st[j][0] = -1;
				st[j][1] = -1;
				i += ft_strlen(var->t_var[j]);
				j++;
			}
		}
		else
		{
			var->n_cmd[k] = cmd[i];
			st[j][0] = -1;
			st[j][1] = -1;
		}
		if (cmd[i] == '$' && !ft_is_shell_var(var->t_var[j]))
			j++;
	}

}

int	**ft_replace_var(t_shell *shell, char **cmd)
{
	t_var	*var;
	int	**st_pos;

	if (ft_strichr(*cmd, '$') == -1)
		return (NULL);
	var = ft_track(ft_memalloc(sizeof(t_var)), &(shell)->t_pars);
	var->l_var = ft_get_nb_var(*cmd);
	var->t_var = (char **)malloc(sizeof(char *) * (var->l_var + 1));
	st_pos = ft_create_tab_int(var->l_var + 1, 2);
	var->p_bool = ft_track((int *)ft_memalloc(sizeof(int) * (var->l_var + 1)), &(shell)->t_pars);
	if (!st_pos || !var->t_var || !var->p_bool)
		return (NULL);
	ft_track_tab((void **)st_pos, &(shell)->t_pars);
	ft_get_var_in_tab(var, *cmd);
	var->l_full = ft_get_full_len_var(shell, var) + ft_strlen(*cmd) + 1;
	var->n_cmd = ft_track((char *)ft_memalloc(sizeof(char) * var->l_full), &(shell)->t_pars);
	ft_check_quote(var, *cmd);
	ft_completed_var_in_cmd(shell, var, *cmd, st_pos);
	int i = 0;
	while (i < var->l_var)
	{
		printf("pos[0]|pos[1]|p_ool|%d|%d|%d|\n", st_pos[i][0],st_pos[i][1], var->p_bool[i]);
		i++;
	}
	*cmd = var->n_cmd;
	return (st_pos);
}
