/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_tools1_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges & jmilhas <x@student.42lyon.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 00:01:38 by aartiges &        #+#    #+#             */
/*   Updated: 2022/03/06 00:01:40 by aartiges &       ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mini_shell.h"

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
