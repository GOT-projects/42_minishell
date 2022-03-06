/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_tools_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges & jmilhas <x@student.42lyon.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 00:01:55 by aartiges &        #+#    #+#             */
/*   Updated: 2022/03/06 00:02:04 by aartiges &       ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mini_shell.h"

/**
* @brief function check if has wildcard
* 
* @param char **cmd
* @return  Return bool
*/
int	ft_check_wildcard(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (ft_strichr(cmd[i], '*') > -1)
			return (1);
		i++;
	}
	return (0);
}

int	ft_ch_wd_var(t_shell *shell, char *cmd)
{
	char	*tmp;
	char	*var;
	int		i;
	int		len;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '$')
		{
			len = ft_get_len_var(cmd + i + 1);
			tmp = ft_strndup(cmd + i + 1, len);
			var = ft_get_env_val(ft_get_env_key(shell->env, tmp));
			if (var && ft_strichr(var, '*') > -1)
			{
				free (tmp);
				return (1);
			}
			if (tmp)
				free(tmp);
		}
		i++;
	}
	return (0);
}

int	ft_check_wild(char **cmd, int *wd)
{
	int	ret;
	int	i;
	int	j;

	i = 0;
	j = 0;
	ret = 0;
	while (cmd[i])
	{
		if (ft_strichr(cmd[i], '*') > -1)
		{
			if (wd[j] == 1)
				ret++;
			j++;
		}
		i++;
	}
	return (ret);
}

/**
* @brief function len of the dir
* 
* @param char *p_dir
* @return  Return len
*/
int	ft_len_dir(char *p_dir)
{
	struct dirent	*dir;
	DIR				*d;
	int				len;

	len = 0;
	d = opendir(p_dir);
	if (d)
	{
		dir = readdir(d);
		len++;
		while (dir != NULL)
		{
			dir = readdir(d);
			len++;
		}
	}
	closedir(d);
	return (len);
}

int	ft_tablen(char **t)
{
	int	i;

	i = 0;
	while (t[i])
		i++;
	return (i);
}
