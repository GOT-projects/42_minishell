#include "../../../includes/mini_shell.h"

int	ft_len_quote(char *cmd)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (cmd[i])
	{
		if (ft_c_quote(cmd[i]))
			len++;
		i++;
	}
	return len;
}

void	ft_complete_tab_quote(t_quote *quote, char *cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
       while (cmd[i])
       {
		if (ft_c_quote(cmd[i]))
		{
			quote->pos[j] = cmd[i];
			j++;
		}
       	i++;
       }
}

void	ft_while_quote(t_quote *quote, int *d, int **st, char *cmd)
{
	while (d[0] < st[d[2]][1])
	{
		if (ft_c_quote(cmd[d[0]]))
			quote->p_bool[d[1]++] = 1;
		d[0] += 1;
	}
	d[2] += 1;
}
