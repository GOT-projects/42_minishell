/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges & jmilhas <x@student.42lyon.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 19:37:25 by aartiges &        #+#    #+#             */
/*   Updated: 2022/02/21 19:37:28 by aartiges &       ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

/* function creer elem for the list chainé
 * @param1 str add to list
 * @param2 struct tracker malloc
 * @return (stack)*/
t_env	*ft_create_envp(char *key, char *value, t_track **t)
{
	t_env	*stack;
	char	*m_key;
	char	*m_value;

	stack = ft_track((t_env *)malloc(sizeof(*stack)), t);
	m_key = ft_track(ft_memalloc(sizeof(char *) * ft_strlen(key) + 1), t);
	m_value = ft_track(ft_memalloc(sizeof(char *) * ft_strlen(value) + 1), t);
	if (!m_key || !m_value || !stack)
		return (NULL);
	m_key = ft_strcpy(m_key, key);
	if (value != NULL)
		m_value = ft_strcpy(m_value, value);
	else
		m_value = NULL;
	stack->key = m_key;
	stack->value = m_value;
	stack->next = NULL;
	stack->prev = NULL;
	return (stack);
}

/* function va au dernier node
 * @param1 t_envp lst
 * @return (stack)*/
t_env	*ft_last(t_env *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

/* function add node en dernier pos
 * @param1 t_envp **lst
 * @param2 t_envp *elem
 * @return (stack)*/
void	ft_add_back(t_env **alst, t_env *ne)
{
	t_env	*elem;

	if (ne == NULL || alst == NULL)
		return ;
	if (*alst == NULL)
	{
		*alst = ne;
		return ;
	}
	elem = ft_last(*alst);
	elem->next = ne;
	ne->prev = elem;
}
