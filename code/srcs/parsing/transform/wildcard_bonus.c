/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges & jmilhas <x@student.42lyon.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 00:02:13 by aartiges &        #+#    #+#             */
/*   Updated: 2022/03/06 00:02:16 by aartiges &       ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mini_shell.h"

/**
* @brief function check if is dir or not
* 
* @param t_wild *wd;
* @param char *cmd;
* @return  Return (bool);
*/
int	ft_check_dir_cmd(t_wild *wd, char *cmd)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (cmd[i])
	{
		if (cmd[i] == '.' && cmd[i + 1] == '/')
			check++;
		else if (check && cmd[i] == '/' && cmd[i - 1] != '.')
			return (0);
		i++;
	}
	if (check == 1)
	{
		wd->c_dir = 1;
		return (1);
	}
	return (0);
}

/**
* @brief function check wildcard
* if true return true
* 
* @param t_wild wd
* @param1 char *cmd 
* @return  Return bool;
*/
int	ft_get_wildcard(char *wild, char *cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (wild[i] || cmd[j])
	{
		if (wild[i] == '*' && ft_strichr(wild + i + 1, '*')
			== -1 && ft_end_wd(wild + i, cmd + j))
			return (1);
		if (wild[i] == '*' && wild[i + 1] == '*')
			i++;
		else if (wild[i] == '*' && wild[i++] == '*')
			while (cmd[j] && cmd[j] != wild[i])
				j++;
		else if (wild[i] == cmd[j] && wild[i] == cmd[j++])
			i++;
		else
			return (0);
	}
	return (1);
}

static char	**ft_add_wild_to_cmd(t_wild *wd, char **cmd, int index)
{
	char	**tmp;
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	tmp = (char **)ft_memalloc(sizeof(char *) * (wd->len + ft_tablen(cmd) + 1));
	if (!tmp)
		return (cmd);
	while (cmd[i])
	{
		j = 0;
		while (wd->full_dir[j] && i == index)
		{
			if (ft_get_wildcard(cmd[i], wd->full_dir[j]))
			{
				if (wd->c_dir)
					tmp[k] = ft_join("./%s", wd->full_dir[j]);
				else
					tmp[k] = ft_strdup(wd->full_dir[j]);
				k++;
			}
			j++;
		}
		if (i != index)
			tmp[k++] = ft_strdup(cmd[i]);
		i++;
	}
	return (tmp);
}

/**
* @brief function add wildcard in tab
* 
* @param t_shell *shell
* @param t_wild *wild
* @param char **cmd
* @return  Return void
*/
char	**ft_get_wild(t_shell *shell, t_wild *wd, char **cmd, int *st)
{
	char	**tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (cmd[i])
	{
		tmp = NULL;
		wd->c_dir = 0;
		if (ft_strichr(cmd[i], '*') > -1 && st[j++])
		{
			if (cmd[i][0] == '.' && cmd[i][1] != '/')
				ft_get_dir_hid(wd->full_dir, ".");
			else 
				ft_get_dir(wd->full_dir, "./");
			if (ft_check_dir_cmd(wd, cmd[i]))
				ft_strcpy(cmd[i], cmd[i] + 2);
			tmp = ft_add_wild_to_cmd(wd, cmd, i);
			ft_track_free_tab(&(shell)->t_pars, (void **)cmd);
			ft_track_tab((void **)tmp, &(shell)->t_pars);
			ft_track_tab((void **)wd->full_dir, &(shell)->t_pars);
			cmd = tmp;
		}
		i++;
	}
	return (cmd);
}

/**
* @brief add wild to the **cmd past
* the function track and free the las cmd past;
* 
* @param t_shell shell
* @param char **cmd
* @return  Return cmd with new wildcard
*/
char	**ft_wildcard(t_shell *shell, char **cmd, int *wd)
{
	t_wild	*wild;

	if (!cmd[0])
		return (cmd);
	if (!ft_check_wildcard(cmd) || !ft_check_wild(cmd, wd))
		return (cmd);
	wild = ft_track(ft_memalloc(sizeof(t_wild)), &shell->t_pars);
	if (!wild)
		return (cmd);
	wild->len = ft_len_dir(".");
	wild->full_dir = (char **)ft_memalloc(sizeof(char *) * (wild->len + 1));
	if (!wild->full_dir)
		return (cmd);
	cmd = ft_get_wild(shell, wild, cmd, wd);
	ft_track_free_tab(&(shell)->t_pars, (void **)wild->full_dir);
	return (cmd);
}
