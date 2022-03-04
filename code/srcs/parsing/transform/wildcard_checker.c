
#include "../../../includes/mini_shell.h"

int	ft_len_wd(char **cmd)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (cmd[i])
	{
		if (ft_strichr(cmd[i], '*'))
			len++;
		i++;
	}
	return (len);
}

int	ft_check_is_dir(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (!i && cmd[i] == '/')
			return (0);
		else if (cmd[i] == '.' && cmd[i + 1] == '.')
			return (0);
		else if (cmd[i] == '.' && cmd[i + 1] == '/')
			i++;
		else if (i != 0 && cmd[i] == '/' && cmd[i - 1] != '.')
			return (0);
		i++;
	}
	return (1);
}

int	ft_check_is_quote(char *cmd)
{
	int	i;

	i = 0;
	if (ft_strichr(cmd, DOUBLE_QUOTE) > -1)
		return (0);
	if (ft_strichr(cmd, SIMPLE_QUOTE) > -1)
		return (0);
	return (1);
}
int	ft_control_wd(char *cmd)
{
	int	i;

	i = 0;
	if (!ft_check_is_dir(cmd))
		return (0);
	if (!ft_check_is_quote(cmd))
		return (0);
	return (1);
}

/**
* @brief function check the wildcard
* if can be use or not
* 
* @param char **cmd
* @return  Return (tab bool);
*/
int	*ft_checker_wildcard(t_shell *shell, char **cmd)
{
	int	*wd;
	int	l_wd;
	int	i;
	int	j;

	i = -1;
	j = 0;
	l_wd = ft_len_wd(cmd);
	wd = ft_track((int *)ft_memalloc(sizeof(int) * (l_wd + 1)), &(shell)->t_pars);
	if (!wd)
		return (NULL);
	while (cmd[++i])
	{
		if (ft_strichr(cmd[i], '*') > -1)
		{
			if (ft_control_wd(cmd[i]))
				wd[j] = 1;
			else
				wd[j] = 0;
			printf("wd [%d]\n", wd[j]);
			j++;
		}
	}
	return (wd);
}
