#include "../../includes/mini_shell.h"

/* function creer elem for the list chainé
 * @param1 str add to list
 * @param2 struct tracker malloc
 * @return (stack)*/
t_envp	*ft_create_envp(char *str, t_track *t)
{
	t_envp	*stack;
	char	*envp;

	stack = ft_track((t_envp *)malloc(sizeof(*stack)), t);
	envp = ft_track(ft_memalloc(sizeof(char *) * ft_strlen(str) + 1), t);
	envp = ft_strcpy(envp, str);
	stack->envp = envp;
	stack->next = NULL;
	stack->prev = NULL;
	return (stack);
}

/* function va au dernier node
 * @param1 t_envp lst
 * @return (stack)*/
t_envp	*ft_last(t_envp *lst)
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
void	ft_add_back(t_envp **alst, t_envp *ne)
{
	t_envp	*elem;

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

/* function check si str et dans une list
 * @param1 t_envp *lst
 * @return (lst trouve)*/
int	ft_check_lst(t_envp *lst, char *s)
{
	t_envp	*elem;
	int	i;
	int	index;

	i = 0;
	elem = lst;
	index = ft_strichr(s, '=');
	if (index == -1)
		index = ft_strlen(s);
	while (elem)
	{
		if (ft_strncmp(elem->envp, s, index) == 0)
			return (i);
		elem = elem->next;
		i++;
	}
	return (-1);
}
