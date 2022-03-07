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
* @brief function check the wild after *
* 
* @param char *wd;
* @param char	*cmd;
* @return  retur (bool);
*/
int	ft_end_wd(char *wd, char *cmd)
{
	int	i;
	int	j;

	i = ft_strlen(wd);
	j = ft_strlen(cmd);
	while (i > 0 && j > 0)
	{
		if (wd[i] != cmd[j])
			return (0);
		i--;
		j--;
	}
	if (i > 1)
		return (0);
	return (1);
}

/**
* @brief function add dir to wild->full_dir
* 
* @param t_wild *wild, char *p_dir
* @return  Return void
*/
void	ft_get_dir(char **full, char *p_dir)
{
	struct dirent	*dir;
	DIR				*d;
	int				i;

	i = 0;
	d = opendir(p_dir);
	if (d)
	{		
		dir = readdir(d);
		while (dir != NULL)
		{
			if (dir->d_name[0] != '.')
				full[i++] = ft_strdup(dir->d_name);
			dir = readdir(d);
		}
	}
	full[i++] = NULL;
	closedir(d);
}

/**
* @brief function add dir hidden to wild->full_dir
* 
* @param t_wild *wild, char *p_dir
* @return  Return void
*/
void	ft_get_dir_hid(char **full, char *p_dir)
{
	struct dirent	*dir;
	DIR				*d;
	int				i;

	i = 0;
	d = opendir(p_dir);
	if (d)
	{		
		dir = readdir(d);
		while (dir != NULL)
		{
			if (dir->d_name[0] == '.')
				full[i++] = ft_strdup(dir->d_name);
			dir = readdir(d);
		}
	}
	full[i++] = NULL;
	closedir(d);
}

/**
* @brief function replace dir with ./ or not
* 
* @param t_wild *wd
* @param int	*d
* @return  new string
*/
char	*ft_alloc_dir(t_wild *wd, int *d)
{
	char	*tmp;

	if (wd->c_dir)
		tmp = ft_join("./%s", wd->full_dir[d[1]]);
	else
		tmp = ft_strdup(wd->full_dir[d[1]]);
	return (tmp);
}
