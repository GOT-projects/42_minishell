/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_var_tool1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges & jmilhas <x@student.42lyon.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 00:02:06 by aartiges &        #+#    #+#             */
/*   Updated: 2022/03/06 00:02:08 by aartiges &       ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mini_shell.h"

int	**ft_catch_dollar_var(t_var *var, t_shell *shell, int **st, int **d)
{
	char	*tmp;

	tmp = ft_itoa(shell->last_exit_status);
	var->n_cmd = ft_strcat(var->n_cmd, tmp);
	st[(*d)[1]][0] = (*d)[2];
	st[(*d)[1]][1] = ft_strlen(tmp) + (*d)[2];
	(*d)[0] += ft_strlen(var->t_var[(*d)[1]]);
	(*d)[1] += 1;
	free(tmp);
	return (st);
}

/**
* @brief function allocation wd->full_dir
* 
* @param t_wild *wild
* @return  Return bool
*/
int	ft_all(t_wild *wd)
{
	wd->full_dir = (char **)ft_memalloc(sizeof(char *) * (wd->len + 1));
	if (!wd->full_dir)
		return (0);
	return (1);
}

void	ft_free_add(t_shell *shell, t_wild *wd, char **cmd)
{
	ft_track_free_tab(&(shell)->t_pars, (void **)cmd);
	ft_track_tab((void **)wd->full_dir, &(shell)->t_pars);
}
