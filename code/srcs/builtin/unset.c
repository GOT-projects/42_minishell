#include "../../includes/mini_shell.h"

/* fonction unset var in list
* @param1 t_envp *lst
* @param2 char *unset
* @return (exit) */
/* int	ft_unset_var(t_envp *lst, char *unset) */
/* { */
/* 	t_envp	*elem; */
/* 	t_envp	*tmp; */

/* 	elem = lst; */
/* 	if (ft_check_var(elem->envp, unset, '=') == true) */
/* 	{ */
/* 		elem = elem->next; */
/* 		elem->prev = NULL; */
/* 		return (EXIT_SUCCESS); */
/* 	} */
/* 	while (elem) */
/* 	{ */
/* 		if (ft_check_var(elem->envp, unset, '=') == true) */
/* 		{ */
/* 			tmp = elem; */
/* 			if (elem->next != NULL) */
/* 				elem->next->prev = tmp->prev; */
/* 			if (elem->prev != NULL) */
/* 				elem->prev->next = tmp->next; */
/* 			return (EXIT_SUCCESS); */
/* 		} */
/* 		elem = elem->next; */
/* 	} */
/* 	return (EXIT_FAILURE); */
/* } */

/* /1* fonction unset var in env */
/* * @param1 struct env */
/* * @param2 char *unset */
/* * @return (bool) *1/ */
/* int	ft_unset(t_shell *env, char *unset) */
/* { */
/* 	t_envp	*elem; */
/* 	t_envp	*tmp; */

/* 	elem = env->envp; */
/* 	if (!unset) */
/* 		return (EXIT_FAILURE); */
/* 	ft_unset_var(env->envp, unset); */
/* 	ft_unset_var(env->export, unset); */
/* 	return (EXIT_FAILURE); */
/* } */
