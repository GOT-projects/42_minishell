/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges <aartiges@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 23:42:03 by aartiges          #+#    #+#             */
/*   Updated: 2022/03/02 23:42:05 by aartiges         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mini_shell.h"

static int	ft_change_path(t_shell *shell, char *path)
{
	t_env	*node;
	int		j;

	node = ft_get_env_key(shell->env, "HOME");
	if (!node || !node->value)
		return (EXIT_FAILURE);
	j = 0;
	if (node->value[j] == path[0])
	{
		while (node->value[j] == path[j] && node->value[j])
			j++;
		if (node->value[j] == '\0'
			&& (path[j] == '/' || path[j] == '\0'))
		{
			ft_strcpy(path, path + j);
			return (EXIT_SUCCESS);
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

static char	*ft_buf(t_shell *shell, char *last_ret, char *log_name, char *path)
{
	char	*buf;

	if (shell->last_exit_status == 0)
		buf = ft_join("%s %s %s [-%s %s %s-] %s~%s > %s",
				PURPLE, last_ret, C_NONE, BLUE,
				log_name, C_NONE, CYAN, path, C_NONE);
	else
		buf = ft_join("%s %s %s [-%s %s %s-] %s~%s > %s",
				RED, last_ret, C_NONE, BLUE, log_name,
				C_NONE, CYAN, path, C_NONE);
	return (buf);
}

static char	*ft_buf1(t_shell *shell, char *last_ret, char *log_name, char *path)
{
	char	*buf;

	if (shell->last_exit_status == 0)
		buf = ft_join("%s %s %s [-%s %s %s-] %s %s > %s",
				PURPLE, last_ret, C_NONE, BLUE, log_name,
				C_NONE, CYAN, path, C_NONE);
	else
		buf = ft_join("%s %s %s [-%s %s %s-] %s %s > %s",
				RED, last_ret, C_NONE, BLUE, log_name,
				C_NONE, CYAN, path, C_NONE);
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
	char	*buf;
	char	*log_name;
	char	*last_ret;
	char	path[PATH_MAX];

	buf = NULL;
	ft_bzero(path, sizeof(char) * PATH_MAX);
	ft_get_pwd(path);
	last_ret = ft_itoa(shell->last_exit_status);
	log_name = ft_add_logname(shell);
	if (!ft_change_path(shell, path))
		buf = ft_buf(shell, last_ret, log_name, path);
	else
		buf = ft_buf1(shell, last_ret, log_name, path);
	free(last_ret);
	return (buf);
}
