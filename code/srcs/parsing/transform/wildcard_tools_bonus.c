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
	printf("ret = %d\n", ret);
	return (ret);
}

/**
* @brief function init function wildcard
* 
* @param t_shell *t_shell
* @param t_wild *wild 
* @param int len;
* @return  Return bool
*/
int	ft_init_wild(t_shell *shell, t_wild *wild, int len)
{

	wild->full_dir = (char **)ft_memalloc(sizeof(char *) * (len + 1));
	wild->p_bool = ft_track((int *)ft_memalloc(sizeof(int) * (len + 1)), &(shell)->t_pars);
	if (!wild->full_dir || !wild->p_bool)
		return (0);
	return (1);
}

/**
* @brief function len of the dir
* 
* @param char *p_dir
* @return  Return len
*/
int	ft_len_dir(char *p_dir)
{
	DIR *d;
	struct dirent *dir;
	int	len;

	len = 0;
	d = opendir(p_dir);
    	if (d)
	{
		while ((dir = readdir(d)) != NULL)
			    len++;
	}
	closedir(d);
	return (len);
}

/**
* @brief function add dir to wild->full_dir
* 
* @param t_wild *wild, char *p_dir
* @return  Return void
*/
void	ft_get_dir(t_wild *wild, char *p_dir)
{
	int	i;
	DIR *d;
	struct dirent *dir;

	i = 0;
	d = opendir(p_dir);
    	if (d)
	{
		while ((dir = readdir(d)) != NULL)
		{
			if (ft_strcmp(".", dir->d_name) && ft_strcmp("..", dir->d_name))
				wild->full_dir[i++] = ft_strdup(dir->d_name);
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
