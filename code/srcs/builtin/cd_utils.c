/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges & jmilhas <x@student.42lyon.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 19:16:44 by aartiges &        #+#    #+#             */
/*   Updated: 2022/02/21 19:16:47 by aartiges &       ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

/**
 * @brief get the number of string in a char**
 * 
 * @param args (char**) the array of string
 * @return size_t the length
 */
size_t	ft_nb_args(char **args)
{
	size_t	i;

	i = 0;
	while (args && args[i])
		++i;
	return (i);
}

/**
 * @brief put in str the actual path (pwd)
 * 
 * @param str (char*) the string of destination
 * /!\ str must have a length >= at PATH_MAX
 * @return ** int 0 if success, else it return errno that is > 0
 */
int	ft_get_pwd(char *str)
{
	ft_bzero(str, PATH_MAX * sizeof(char));
	if (!getcwd(str, PATH_MAX))
	{
		ft_putstr_fd("cd: path error\n", 2);
		return (errno);
	}
	return (0);
}
