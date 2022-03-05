/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote_tool.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges & jmilhas <x@student.42lyon.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 00:01:50 by aartiges &        #+#    #+#             */
/*   Updated: 2022/03/06 00:01:51 by aartiges &       ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mini_shell.h"

int	ft_len_quote(char *cmd)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (cmd[i])
	{
		if (ft_c_quote(cmd[i]))
			len++;
		i++;
	}
	return (len);
}

void	ft_complete_tab_quote(t_quote *quote, char *cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd[i])
	{
		if (ft_c_quote(cmd[i]))
		{
			quote->pos[j] = cmd[i];
			j++;
		}
	i++;
	}
}

void	ft_while_quote(t_quote *quote, int *d, int **st, char *cmd)
{
	while (d[0] < st[d[2]][1] - 1)
	{
		if (ft_c_quote(cmd[d[0]]))
			quote->p_bool[d[1]++] = 1;
		d[0] += 1;
	}
	d[2] += 1;
}

void	ft_set_quote(t_quote *quote, int *d, int c)
{
	quote->p_bool[d[1]++] = 0;
	d[3] = c;
}
