/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges & jmilhas <x@student.42lyon.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 00:02:18 by aartiges &        #+#    #+#             */
/*   Updated: 2022/03/06 00:02:23 by aartiges &       ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mini_shell.h"

static void	ft_track_quote(t_quote *quote, int len)
{
	int	j;
	int	state;

	j = 0;
	state = 0;
	while (j < len)
	{
		if (state && state == quote->pos[j])
		{
			quote->p_bool[j++] = 0;
			state = 0;
		}
		else if (!state)
		{
			state = quote->pos[j];
			quote->p_bool[j++] = 0;
		}
		if (state)
			while (quote->pos[j] != state)
				quote->p_bool[j++] = 1;
	}
}

static char	*ft_replace_cmd_state(t_shell *shell, t_quote *quote, char *cmd)
{
	char	*n_cmd;
	int		dc[3];

	ft_bzero(dc, sizeof(int) * 3);
	n_cmd = ft_track((char *)ft_memalloc(sizeof(char)
				* ft_strlen(cmd)), &(shell)->t_pars);
	if (! n_cmd)
		return (NULL);
	while (cmd[dc[0]])
	{
		if (cmd[dc[0]] != DOUBLE_QUOTE && cmd[dc[0]] != SIMPLE_QUOTE)
			n_cmd[dc[2]++] = cmd[dc[0]];
		else if (ft_c_quote(cmd[dc[0]]) && quote->p_bool[dc[1]] == 1)
		{
			n_cmd[dc[2]++] = cmd[dc[0]];
			dc[1]++;
		}
		else if (ft_c_quote(cmd[dc[0]]) && quote->p_bool[dc[1]] == 0)
			dc[1]++;
		dc[0]++;
	}
	return (n_cmd);
}

static void	ft_track_quote_states(t_quote *quote, char *cmd, int **st)
{
	int	d[4];

	ft_bzero(d, sizeof(int) * 4);
	while (cmd[d[0]])
	{
		if (d[0] >= st[d[2]][0] && d[0] < st[d[2]][1])
			ft_while_quote(quote, d, st, cmd);
		else if (!d[3] && ft_c_quote(cmd[d[0]]))
			ft_set_quote(quote, d, cmd[d[0]]);
		else if (d[3] && ft_c_quote(cmd[d[0]]) && d[3] != cmd[d[0]])
			quote->p_bool[d[1]++] = 1;
		else if (d[3] && ft_c_quote(cmd[d[0]]) && d[3] == cmd[d[0]])
		{
			d[3] = 0;
			quote->p_bool[d[1]++] = 0;
		}
		d[0]++;
	}
}

static int	ft_gen_pos(t_shell *shell, t_quote *quote, char *cmd, int **states)
{
	if (ft_strichr(cmd, DOUBLE_QUOTE) == -1
		&& ft_strichr(cmd, SIMPLE_QUOTE) == -1)
		return (0);
	quote->len = ft_len_quote(cmd);
	if (quote->len == 1)
		return (0);
	quote->pos = ft_track((int *)ft_memalloc(sizeof(int)
				* quote->len), &(shell)->t_pars);
	quote->p_bool = ft_track((int *)ft_memalloc(sizeof(int)
				* quote->len), &(shell)->t_pars);
	if (!quote->p_bool || !quote->pos)
		return (0);
	ft_complete_tab_quote(quote, cmd);
	if (states)
		ft_track_quote_states(quote, cmd, states);
	else
		ft_track_quote(quote, quote->len);
	return (1);
}

/* @function remove quote of the string */
/* with change the quote the var */
/* @char *cmd */
/* @return (int) */
char	*ft_remove_quote(t_shell *shell, char *cmd, int **states)
{
	t_quote	*quote;
	char	*n_cmd;

	quote = ft_track(ft_memalloc(sizeof(t_quote)), &(shell)->t_pars);
	if (!ft_gen_pos(shell, quote, cmd, states))
		return (cmd);
	n_cmd = ft_replace_cmd_state(shell, quote, cmd);
	ft_track_free(&(shell)->t_pars, cmd);
	return (n_cmd);
}
