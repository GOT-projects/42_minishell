/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_forgot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges & jmilhas <x@student.42lyon.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 20:14:14 by aartiges &        #+#    #+#             */
/*   Updated: 2022/02/21 20:14:16 by aartiges &       ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mini_shell.h"

/**
 * @brief check if a string is empty (empty is a string null or a string with
 * blanks)
 * 
 * @param str the string to check
 * @return _Bool true if empty, false else
 */
_Bool	ft_is_empty(char *str)
{
	size_t	i;

	if (!str)
		return (true);
	i = 0;
	while (str[i])
	{
		if (!ft_strchr(SPACES, str[i]))
			return (false);
		++i;
	}
	return (true);
}

/**
 * @brief function demand the end of the command (ex: ls |) at the parsing
 * 
 * @param shell the shell
 * @return ** int 0 if success, 1 else
 */
int	ft_get_forgot_cmd(t_shell *shell)
{
	char	*forgot_pipe;
	char	*new_cmd;

	forgot_pipe = readline("and the next? > ");
	while (forgot_pipe && ft_is_empty(forgot_pipe))
	{
		free(forgot_pipe);
		forgot_pipe = readline("and the next? > ");
	}
	if (forgot_pipe)
	{
		new_cmd = ft_strjoin(shell->operation->to_parse, forgot_pipe);
		free(forgot_pipe);
		ft_track_free(&(shell->t_pars), shell->operation->to_parse);
		if (!new_cmd)
			return (1);
		shell->operation->to_parse = new_cmd;
		ft_track(shell->operation->to_parse, &(shell->t_pars));
	}
	return (0);
}
