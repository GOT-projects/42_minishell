#include "../../../includes/mini_shell.h"

static int	ft_change_path(t_shell *shell, char *path)
{
	t_env	*node;
	int	i;
	int	j;

	node = ft_get_env_key(shell->env, "USER");
	if (!node || !node->value)
		return (EXIT_FAILURE);
	i = -1;
	while (path[++i])
	{
		j = 0;
		if (node->value[j] == path[i])
		{
			while (node->value[j] == path[i + j] && node->value[j])
				j++;
			if (node->value[j] == '\0' &&
				(path[i + j] == '/' || path[i + j] == '\0'))
			{
				ft_strcpy(path, path + j + i);
				return (EXIT_SUCCESS);
			}
		}
	}
	return (EXIT_FAILURE);
}

static char	*ft_add_logname(t_shell *shell)
{
	char	*buf;

	buf = ft_get_env_val(ft_get_env_key(shell->env, "LOGNAME"));
	if (!buf)
		return (ft_strdup("NONE"));
	return (buf);
}
/**
* @brief function create the prompte of readline 
* 
* @param t_shell *shell
* @return  Return (buf)
*/
char	*ft_create_str_read_line(t_shell *shell)
{
	char	*buf = NULL;
	char	*log_name;
	char	*last_ret;
	char	path[PATH_MAX];
	
	ft_bzero(path, sizeof(char) * PATH_MAX);
	ft_get_pwd(path);
	last_ret = ft_itoa(shell->last_exit_status);
	log_name = ft_add_logname(shell);
	;
	if (!ft_change_path(shell, path))
	{
		if (shell->last_exit_status == 0)
			buf = ft_join("%s %s %s [-%s %s %s-] %s~%s > %s",PURPLE, last_ret,C_NONE, BLUE, log_name, C_NONE, CYAN, path, C_NONE);
		else
			buf = ft_join("%s %s %s [-%s %s %s-] %s~%s > %s",RED, last_ret,C_NONE, BLUE, log_name, C_NONE, CYAN, path, C_NONE);
	}
	else
	{
		if (shell->last_exit_status == 0)
			buf = ft_join("%s %s %s [-%s %s %s-] %s %s > %s",PURPLE, last_ret,C_NONE, BLUE, log_name, C_NONE, CYAN, path, C_NONE);
		else
			buf = ft_join("%s %s %s [-%s %s %s-] %s %s > %s",RED, last_ret,C_NONE, BLUE, log_name, C_NONE, CYAN, path, C_NONE);
	}
	free(last_ret);
	return (buf);
}

