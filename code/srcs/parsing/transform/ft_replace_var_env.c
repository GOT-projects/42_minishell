/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_var_env.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges & jmilhas <x@student.42lyon.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 00:01:42 by aartiges &        #+#    #+#             */
/*   Updated: 2022/03/06 00:01:44 by aartiges &       ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mini_shell.h"

static char	**ft_get_var_in_tab(t_var *var, char *cmd)
{
	int	d[5];

	ft_bzero(d, sizeof(int) * 5);
	while (cmd[d[0]])
	{
		if (!d[4] && ft_c_quote(cmd[d[0]]))
			d[4] = cmd[d[0]];
		else if (d[4] && cmd[d[0]] == d[4])
			d[4] = 0;
		if (cmd[d[0]] == '$')
		{
			d[3] = ft_get_len_var(cmd + d[0] + 1);
			if (d[3] > 0)
				var->t_var[d[1]] = ft_strndup(cmd + d[0] + 1, d[3]);
			else
				var->t_var[d[1]] = ft_strndup(cmd + d[0], 1);
			d[1]++;
		}
		d[0]++;
	}
	var->t_var[d[1]] = NULL;
	return (var->t_var);
}

static void	ft_check_quote(t_var *var, char *cmd)
{
	int	i;
	int	j;
	int	state;

	i = 0;
	j = 0;
	state = 0;
	while (cmd[i])
	{
		if (ft_c_quote(cmd[i]) && !state)
			state = cmd[i];
		else if (ft_c_quote(cmd[i]) && state == cmd[i])
			state = 0;
		else if ((!state || state == DOUBLE_QUOTE) && cmd[i] == '$')
			var->p_bool[j++] = 1;
		else if (state == SIMPLE_QUOTE && cmd[i] == '$')
			var->p_bool[j++] = 0;
		i++;
	}
}

static void	ft_check_tmp(t_var *var, int *d, int **st, t_shell *shell)
{
	char	*tmp;

	if (!ft_strcmp("?", var->t_var[d[1]]))
	{
		st = ft_catch_dollar_var(var, shell, st, &d);
		return ;
	}
	tmp = ft_get_env_val(ft_get_env_key(shell->env, var->t_var[d[1]]));
	if (tmp)
	{
		var->n_cmd = ft_strcat(var->n_cmd, tmp);
		st[d[1]][0] = d[2];
		st[d[1]][1] = ft_strlen(tmp) + d[2];
		d[0] += ft_strlen(var->t_var[d[1]]);
		d[1]++;
	}
	else
	{
		ft_set_st(st, d[1]);
		d[0] += ft_strlen(var->t_var[d[1]]);
		d[1]++;
	}
}

static void	ft_completed_var(t_shell *shell, t_var *var, char *cmd, int **st)
{
	int		d[3];

	ft_bzero(d, sizeof(int) * 3);
	d[0] = -1;
	while (cmd[++d[0]])
	{
		while (var->n_cmd[d[2]])
			d[2]++;
		if (var->p_bool[d[1]] && cmd[d[0]] == '$'
			&& ft_is_var(var->t_var[d[1]]))
			ft_check_tmp(var, d, st, shell);
		else
		{
			var->n_cmd[d[2]] = cmd[d[0]];
			ft_set_st(st, d[1]);
		}
		if (cmd[d[0]] == '$' && !ft_is_shell_var(var->t_var[d[1]]))
			d[1]++;
	}
	ft_set_st(st, d[1]);
}

/**
* @brief function replace the $ by the var of env lst
* return **tab with th position of var and len 
* for not modify the quote inside the var 
* 
* @param t_shell *shell
* @param char **cmd
* @return  Return (**tab)
*/
int	**ft_replace_var(t_shell *shell, char **cmd)
{
	t_var	*var;
	int		**st_pos;

	if (ft_strichr(*cmd, '$') == -1)
		return (NULL);
	var = ft_track(ft_memalloc(sizeof(t_var)), &(shell)->t_pars);
	var->l_var = ft_get_nb_var(*cmd);
	var->t_var = (char **)malloc(sizeof(char *) * (var->l_var + 1));
	st_pos = ft_create_tab_int(var->l_var + 1, 2);
	var->p_bool = ft_track((int *)ft_memalloc(sizeof(int)
				* (var->l_var + 1)), &(shell)->t_pars);
	if (!st_pos || !var->t_var || !var->p_bool)
		return (NULL);
	ft_track_tab((void **)st_pos, &(shell)->t_pars);
	ft_get_var_in_tab(var, *cmd);
	var->l_full = ft_get_full_len_var(shell, var) + ft_strlen(*cmd) + 1;
	var->n_cmd = ft_track((char *)ft_memalloc(sizeof(char)
				* var->l_full), &(shell)->t_pars);
	ft_check_quote(var, *cmd);
	ft_completed_var(shell, var, *cmd, st_pos);
	*cmd = var->n_cmd;
	ft_free_2d(var->t_var);
	return (st_pos);
}
