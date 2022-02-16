#include "../../../includes/mini_shell.h"

static void	ft_check_quote(char *cmd, int *check, int *j, int i)
{
	if (check[0] == 0)
	{
		check[0] = 1;
		check[1] = cmd[i + *j];
		*j += 1;
	}
	else if (check[0] == 1 && check[1] == cmd[i + *j])
	{
		check[0] = 0;
		check[1] = 0;
		*j += 1;
	}
}

static char	*ft_init_check_quote(t_shell *shell, int *check, char *cmd)
{
	char	*n_cmd;

	ft_bzero(check, sizeof(int) * 2);
	if (ft_strichr(cmd, '\'') == -1 && ft_strichr(cmd, '"') == -1)
		return (NULL);
	n_cmd = ft_track((char *)ft_memalloc(sizeof(char) * ft_strlen(cmd)), &(shell)->t_pars);
	if (!n_cmd)
		return (NULL);
	return (n_cmd);
}

/* @function remove quote of the string */ 
/* @char *cmd */
/* @return (int) */
char	*ft_remove_quote(t_shell *shell, char *cmd)
{
	char	*n_cmd;
	int		i;
	int		j;
	int		check[2];

	i = 0;
	j = 0;
	n_cmd = ft_init_check_quote(shell, check, cmd);
	if (!n_cmd)
		return (cmd);
	while (cmd[i + j])
	{
		if (cmd[i + j] == DOUBLE_QUOTE || cmd[i + j] == SIMPLE_QUOTE)
			ft_check_quote(cmd, check, &j, i);
		n_cmd[i] = cmd[i + j];
		if (cmd[i + j] == '\0')
			break;
		i++;
	}
	ft_track_free(&(shell)->t_pars, cmd);
	cmd = n_cmd;
	return (n_cmd);
}
