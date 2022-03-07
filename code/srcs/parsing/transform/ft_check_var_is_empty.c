/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_var_is_empty.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges & jmilhas <x@student.42lyon.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 00:01:42 by aartiges &        #+#    #+#             */
/*   Updated: 2022/03/07 21:46:30 by aartiges &       ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mini_shell.h"

char	**ft_remove_empty_cmd(char **cmd, int index)
{
	while (cmd[index])
	{
		cmd[index] = cmd[index + 1];
		index++;
	}
	return (cmd);
}
