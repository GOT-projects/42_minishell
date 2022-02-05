
#include "../../includes/mini_shell.h"

/* function len de lst
 * @param1 t_envp *lst	
 * @return (len)*/
size_t	ft_lstlen(t_envp *lst)
{
	t_envp *elem;
	size_t	i;

	i = 0;
	elem = lst;
	while (elem)
	{
		elem = elem->next;
		i++;
	}
	return (i);
}

/* function creer tab from list
 * @param1 t_envp *lst	
 * @return (tab of list)*/
char	**ft_lst_to_tab(t_envp *lst)
{
	char	**conv;
	t_envp	*elem;
	size_t	i;

	elem = lst;
	i = 0;
	conv = (char **)malloc(sizeof(char *) * (ft_lstlen(lst) + 1));
	if (!conv)
		return (NULL);
	while (elem)
	{
		conv[i] = ft_strdup(elem->envp);
		if (!conv[i])
			return (NULL);
		elem = elem->next;
		i++;
	}
	conv[i] = NULL;
	return (conv);
}
