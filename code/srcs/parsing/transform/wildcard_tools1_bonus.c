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
* @brief function get the len of wildcard found
* if true add true in p_bool
* 
* @param t_wild wd
* @param1 char *cmd 
* @return  Return void;
*/
void	ft_add_wild(t_wild *wd, char **cmd)
{
	int	i;
	int	j;

	j = 0;
	while (cmd[j])
	{
		i = 0;
		if (ft_check_dir_cmd(wd, cmd[j]))
			cmd[j] = ft_strcpy(cmd[j], cmd[j] + 2);
		while (wd->full_dir[i])
		{
			if (cmd[j][0] == '*' && cmd[j][1] == '\0')
				wd->p_bool[i] = 1;
			else if (ft_check_dir_cmd(wd, cmd[j]))
				wd->p_bool[i] = 1;
			else if (ft_get_wildcard(cmd[j], wd->full_dir[i]))
				wd->p_bool[i] = 1;
			else
				wd->p_bool[i] = 0;
			i++;
		}
		j++;
	}
}

/**
* @brief function check is the len of 
* wildcard found	
* 
* @param t_wild *wd
* @return  return (len);
*/
int	ft_check_wild_dir(t_wild *wd)
{
	int	ret;
	int	i;

	i = 0;
	ret = 0;
	while (wd->full_dir[i])
	{
		if (wd->p_bool[i])
			ret++;
		i++;
	}
	return (ret);
}

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
* @brief function add ./ to the ./
* 
* @param t_wild *wd;
* @param t_shell *shell;
* @param char **cmd;
* @return  Return (**cmd);
*/
char	**ft_add_dir_in_wild(t_wild *wd, t_shell *shell, char **cmd)
{
	char	**tmp;
	int		dc[3];

	dc[0] = -1;
	tmp = ft_alloc_tab_from_tab(cmd);
	if (!tmp)
		return (NULL);
	while (cmd[++dc[0]])
	{
		ft_bzero(dc + 1, sizeof(int) * 2);
		while (cmd[dc[0]] && wd->full_dir[dc[1]])
		{
			if (!ft_strcmp(cmd[dc[0]], wd->full_dir[dc[1]]))
				dc[2] = 1;
			if (!ft_strcmp(cmd[dc[0]], wd->full_dir[dc[1]]))
				tmp[dc[0]++] = ft_join("./%s", wd->full_dir[dc[1]]);
			dc[1]++;
		}
		if (dc[2] == 0)
			tmp[dc[0]] = ft_strdup(cmd[dc[0]]);
	}
	ft_track_tab((void **)tmp, &(shell)->t_pars);
	return (tmp);
}
