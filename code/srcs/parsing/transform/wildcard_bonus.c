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
	if (wild[i] == '*' && wild[i + 1] == '\0')
		return (1);
	while (wild[i])
	{
		if (!cmd[j])
			return (0);
		if (wild[i] == '*' && wild[i + 1] == '*')
		{
			i++;
			j++;
		}
		else if (wild[i] == '*')
		{
			i++;
			while (cmd[j] && cmd[j] != wild[i])
				j++;
		}
		else if (wild[i] == cmd[j])
		{
			i++;
			j++;
		}
		else
			return (0);
	}
	if (wild[i] != cmd[j])
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
void	ft_add_wild(t_wild *wd, char *cmd)
{
	int	i;

	i = 0;
	while (wd->full_dir[i])
	{
		if (ft_get_wildcard(cmd, wd->full_dir[i]))
			wd->p_bool[i] = 1;
		else
			wd->p_bool[i] = 0;
		i++;
	}
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
	char	**n_cmd;
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	ft_get_len_wild(wd, cmd);
	n_cmd = (char **)ft_memalloc(sizeof(char *) * (wd->len_cmd + wd->len_wild + 1));
	if (!n_cmd)
		return (NULL);
	while ((i < wd->len_cmd + wd->len_wild + 1) && cmd[k])
	{
		if (i == *id)
		{
			while (wd->full_dir[j])
			{
				if (wd->p_bool[j] == 1)
					n_cmd[i++] = ft_strdup(wd->full_dir[j++]);
				else
					j++;
			}
			k++;
		}
		else
			n_cmd[i++] = ft_strdup(cmd[k++]);
	}
	return (n_cmd);
}

/**
* @brief function add wildcard in tab
* 
* @param t_shell *shell
* @param t_wild *wild
* @param char **cmd
* @return  Return void
*/
char	**ft_get_wild(t_shell *shell, t_wild *wd, char **cmd)
{
	char	**tmp;
	int		i;

	i = 0;
	while (cmd[i])
	{
		if (ft_strichr(cmd[i], '*') > -1)
		{
			ft_add_wild(wd, cmd[i]);
			tmp = ft_wild_to_cmd(wd, cmd, &i);
			if (!tmp)
				return NULL;
			ft_track_free_tab(&(shell->t_pars), (void **)cmd);
			ft_track_tab((void **)tmp, &(shell)->t_pars);
			cmd = tmp;
			i += ft_get_len_p_bool(wd);
		}
		i++;
	}
	cmd[i] = NULL;
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
char	**ft_wildcard(t_shell *shell, char **cmd)
{
	t_wild	*wild;

	if (!cmd[0])
		return (cmd);
	if (!ft_check_wildcard(cmd))
		return (cmd);
	wild = ft_track(ft_memalloc(sizeof(t_wild)), &shell->t_pars);
	if (!wild)
		return (cmd);
	wild->len = ft_len_dir(".");
	ft_init_wild(shell, wild, wild->len);
	ft_get_dir(wild, ".");
	ft_track_tab((void **)wild->full_dir, &(shell)->t_pars);
	cmd = ft_get_wild(shell, wild, cmd);
	return (cmd);
}
