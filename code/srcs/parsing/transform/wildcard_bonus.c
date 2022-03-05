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

/**
* @brief function get the len of wildcard found
* 
* @param t_wild wd
* @return  Return len;
*/
int	ft_get_len_p_bool(t_wild *wd)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (i < wd->len)
	{
		if (wd->p_bool[i] == 1)
			len++;
		i++;
	}
	return (len);
}

/**
* @brief function add wildcard at the good position
*
* 
* @param t_shell *shell
* @param t_wild *wild
* @param int *id 
* @return  Return n_cmd;
*/
char	**ft_wild_to_cmd(t_wild *wd, char **cmd, int *id)
{
	char	**n;
	int		dc[3];

	ft_bzero(dc, sizeof(int) * 3);
	ft_get_len_wild(wd, cmd);
	n = (char **)ft_memalloc(sizeof(char *) * (wd->len_cmd + wd->len_wild + 1));
	if (!n)
		return (NULL);
	while ((dc[0] < wd->len_cmd + wd->len_wild + 1) && cmd[dc[2]])
	{
		if (dc[0] == *id)
		{
			while (wd->full_dir[dc[1]])
				if (wd->p_bool[dc[1]] == 1)
					n[dc[0]++] = ft_strdup(wd->full_dir[dc[1]++]);
			else
					dc[1]++;
			dc[2]++;
		}
		else
			n[dc[0]++] = ft_strdup(cmd[dc[2]++]);
	}
	return (n);
}

/**
* @brief function add wildcard in tab
* 
* @param t_shell *shell
* @param t_wild *wild
* @param char **cmd
* @return  Return void
*/
char	**ft_get_wild(t_shell *shell, t_wild *wd, char **cmd, int *wild)
{
	char	**tmp;
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (cmd[++i])
	{
		tmp = NULL;
		if (ft_strichr(cmd[i], '*') > -1 && wild[j++])
		{
			tmp = ft_wild_to_cmd(wd, cmd, &i);
			if (!tmp)
				return (NULL);
			ft_track_free_tab(&(shell->t_pars), (void **)cmd);
			ft_track_tab((void **)tmp, &(shell)->t_pars);
			cmd = tmp;
			i += ft_get_len_p_bool(wd);
		}
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
	ft_init_wild(shell, wild, wild->len);
	ft_get_dir(wild, ".");
	ft_track_tab((void **)wild->full_dir, &(shell)->t_pars);
	ft_add_wild(wild, cmd);
	if (ft_check_wild_dir(wild))
		cmd = ft_get_wild(shell, wild, cmd, wd);
	if (wild->c_dir == 1)
		cmd = ft_add_dir_in_wild(wild, shell, cmd);
	ft_track_free(&(shell)->t_pars, wild->p_bool);
	ft_track_free_tab(&(shell)->t_pars, (void **)wild->full_dir);
	return (cmd);
}
