
#include "../../../includes/mini_shell.h"

static size_t	ft_get_len_var(char *cmd, size_t state)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (!state && (cmd[i] == ' ' || cmd[i] == '$'))
			return (i);
		else if (state && ((int)state == cmd[i] || cmd[i] == '$'))
			return (i);
		i++;
	}
	return (i);
}

static size_t	ft_get_full_len_var(t_shell *shell, t_var *var)
{
	char	*value;
	size_t	i;
	size_t	len;

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

static size_t	ft_get_nb_var(char *cmd)
{
	size_t	i;
	size_t	len;

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
	size_t	i;
	size_t	j;
	size_t	index;
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
			index = ft_get_len_var(cmd + i + 1, state);
			var->t_var[j] = ft_strndup(cmd + i + 1, index);
			printf("var add  | %s\n", var->t_var[j]);
			j++;
		}
		i++;
	}
	var->t_var[j] = NULL;
	return (var->t_var);
}

static void	ft_check_quote(t_var *var, char *cmd)
{
	size_t	i;
	size_t	j;
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

static void	ft_completed_var_in_cmd(t_shell *shell, t_var *var, char *cmd, size_t **st)
{
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	l;
	char *tmp;

	i = 0;
	j = 0;
	k = 0;
	while (cmd[i])
	{
		l = 0;
		if (cmd[i] == '$' && var->p_bool[j])
		{
			tmp = ft_get_env_val(ft_get_env_key(shell->env, var->t_var[j]));
			if (tmp)
			{
				var->n_cmd = ft_strcat(var->n_cmd, tmp);
				st[j][0] = k;
				st[j][1] = ft_strlen(tmp) + k;
				i += ft_strlen(var->t_var[j]);
				j++;
			}
			else
			{
				st[j][0] = 100000000;
				st[j][1] = 100000000;
				i += ft_strlen(var->t_var[j++]);
			}
			while (var->n_cmd[k])
				k++;
		}
		else if (!var->p_bool)
			while (var->t_var[l])
			{
				i++;
				l++;
			}
		else
			var->n_cmd[k++] = cmd[i];
		i++;
	}
}

size_t	**ft_replace_var(t_shell *shell, char **cmd)
{
	t_var	*var;
	size_t	**st_pos;

	printf("cmd entry %s\n",*cmd);
	if (ft_strichr(*cmd, '$') == -1)
		return (NULL);
	var = ft_track(ft_memalloc(sizeof(t_var)), &(shell)->t_pars);
	var->l_var = ft_get_nb_var(*cmd);
	var->t_var = (char **)malloc(sizeof(char *) * (var->l_var + 1));
	st_pos = ft_create_tab_size_t(var->l_var + 1, 2);
	var->p_bool = ft_track((int *)ft_memalloc(sizeof(int) * (var->l_var + 1)), &(shell)->t_pars);
	if (!st_pos || !var->t_var || !var->p_bool)
		return (NULL);
	ft_track_tab((void **)st_pos, &(shell)->t_pars);
	ft_get_var_in_tab(var, *cmd);
	var->l_full = ft_get_full_len_var(shell, var) + ft_strlen(*cmd) + 1;
	var->n_cmd = ft_track((char *)ft_memalloc(sizeof(char) * var->l_full), &(shell)->t_pars);
	ft_check_quote(var, *cmd);
	ft_completed_var_in_cmd(shell, var, *cmd, st_pos);
	size_t i = 0;
	while (i < var->l_var)
	{
		printf("|%lu|%lu|%d|\n", st_pos[i][0],st_pos[i][1], var->p_bool[i]);
		i++;
	}
	*cmd = var->n_cmd;
	return (st_pos);
}
