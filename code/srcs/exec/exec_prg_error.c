/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_prg_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges <aartiges@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 19:42:24 by aartiges &        #+#    #+#             */
/*   Updated: 2022/03/07 16:13:28 by aartiges         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

/**
 * @brief print errors if the research of the executable not match
 * 
 * @param cmd arguments array of the command (like "ls" "-l" "/")
 * @param error_research the error of the research (future exit status)
 */
void	ft_prg_error_research_path(char **cmd, int error_research)
{
	if (error_research == ERR_403_EXEC || error_research == ERR_404_EXEC)
	{
		ft_putstr_fd(cmd[0], 2);
		if (error_research == ERR_403_EXEC)
			ft_putstr_fd(": Permission denied\n", 2);
		else if (ft_strchr(cmd[0], '/') && error_research == ERR_404_EXEC)
			ft_putstr_fd(": No such file or directory\n", 2);
		else
			ft_putstr_fd(": Command not found\n", 2);
	}
	else
		perror(cmd[0]);
}

/**
 * @brief print the error on signal and return the good exit status
 * 
 * @param prg_name the program name
 * @param status the status of the child process
 * @return int -- 
 */
int	ft_error_exit_process(char *prg_name, int status)
{
	char	*sign;
	char	*tmp;

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (DEBUG)
	{
		if (WIFSIGNALED(status))
		{
			tmp = ft_itoa(WTERMSIG(status));
			sign = ft_join("%s : process terminated due to receipt of \
					signal %s\n",
					prg_name, tmp);
			ft_putstr_fd(sign, 2);
			free(sign);
			free(tmp);
		}
	}
	return (1);
}
