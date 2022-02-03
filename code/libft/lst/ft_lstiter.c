/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmilhas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 23:53:36 by jmilhas           #+#    #+#             */
/*   Updated: 2021/12/16 23:53:36 by jmilhas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*left;

	if (lst != NULL)
	{
		left = lst;
		while (1)
		{
			(*f)(left->content);
			left = left->next;
			if (left == NULL)
				return ;
		}
	}
}
