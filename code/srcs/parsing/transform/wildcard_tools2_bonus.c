/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_tools2_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges & jmilhas <x@student.42lyon.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 00:02:09 by aartiges &        #+#    #+#             */
/*   Updated: 2022/03/06 00:02:12 by aartiges &       ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mini_shell.h"

char	**ft_alloc_tab_from_tab(char **cmd)
{
	char	**tmp;
	int		i;

	i = 0;
	while (cmd[i])
		i++;
	tmp = (char **)ft_memalloc(sizeof(char *) * (i + 1));
	if (!tmp)
		return (NULL);
	return (tmp);
}

/**
* @brief function add dir to wild->full_dir
* 
* @param t_wild *wild, char *p_dir
* @return  Return void
*/
void	ft_get_dir(t_wild *wild, char *p_dir)
{
	struct dirent	*dir;
	DIR				*d;
	int				i;

	i = 0;
	d = opendir(p_dir);
	if (d)
	{	
		dir = readdir(d);
		if (ft_strcmp(".", dir->d_name) && ft_strcmp("..", dir->d_name))
			wild->full_dir[i++] = ft_strdup(dir->d_name);
		while (dir != NULL)
		{
			if (ft_strcmp(".", dir->d_name) && ft_strcmp("..", dir->d_name))
				wild->full_dir[i++] = ft_strdup(dir->d_name);
			dir = readdir(d);
		}
	}
	wild->full_dir[i++] = NULL;
	closedir(d);
}

/**
* @brief function get len of cmd and the wilcard to add
* 
* @param t_wild *wildcard
* @param char **cmd
* @return  Return void
*/
void	ft_get_len_wild(t_wild *wd, char **cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
		wd->len_cmd++;
	i = 0;
	while (i < wd->len)
	{
		if (wd->p_bool[i] == 1)
			wd->len_wild++;
		i++;
	}
}
