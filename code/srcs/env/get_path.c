/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges <aartiges@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 22:51:04 by aartiges          #+#    #+#             */
/*   Updated: 2022/03/02 22:51:05 by aartiges         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

/**
* @brief function get path from lst
* 
* @param t_shell *shell
* @return  Return (path/NULL)
*/
char	**ft_get_path(t_shell *shell)
{
	t_env	*node;

	node = ft_get_env_key(shell->env, "PATH");
	if (node)
		return (ft_strsplit(node->value, ':'));
	return (NULL);
}
