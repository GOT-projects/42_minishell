#include "../../../includes/mini_shell.h"

static int	ft_len_quote(char *cmd)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (cmd[i])
	{
		if (cmd[i] == DOUBLE_QUOTE || cmd[i] == SIMPLE_QUOTE)
			len++;
		i++;
	}
	return len;
}

static void	ft_complete_tab_quote_states(t_quote *quote, char *cmd, int **st)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (cmd[i])
	{
		if ((!st[j]) && (cmd[i] == 34 || cmd[i] == 39))
			quote->pos[k++] = cmd[i];
        	else if ((st[j]) && (cmd[i] == 34 || cmd[i] == 39) && i < st[j][0])
			quote->pos[k++] = cmd[i];
        	if (st[j] && i >= st[j][0])
        	{
            		while (i < st[j][1])
                		i++;
            		j++;
        	}
        	i++;
	}
}

static void	ft_complete_tab_quote(t_quote *quote, char *cmd, int **states)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!states)
	{
		while (cmd[i])
		{
			if (cmd[i] == DOUBLE_QUOTE || cmd[i] == SIMPLE_QUOTE)
			{
				quote->pos[j] = cmd[i];
				j++;
			}
			i++;
		}
	}
	else
		ft_complete_tab_quote_states(quote, cmd, states);
}

static void	ft_track_quote(t_quote *quote, int len)
{
	int	j;
	int	state;

	j = 0;
	state = 0;
	while (j < len)
	{
		if (state && state == quote->pos[j])
		{
			quote->p_bool[j++] = 0;
			state = 0;
		}
		else if (!state)
		{
			state = quote->pos[j];
			quote->p_bool[j++] = 0;
		}
		if (state)
			while (quote->pos[j] != state)
				quote->p_bool[j++] = 1;	
	}
}

static char	*ft_replace_cmd_without_state(t_shell *shell, t_quote *quote, char *cmd)
{
	char	*n_cmd;
	int	dc[3];

	int	i;
	i = 0;
	while (i < quote->len)
	{
		printf("pos |%d|%d| true\n", quote->pos[i], quote->p_bool[i]);
		i++;
	}
	ft_bzero(dc, sizeof(int) * 3);
	n_cmd = ft_track((char *)ft_memalloc(sizeof(char) * ft_strlen(cmd)), &(shell)->t_pars);
	if (! n_cmd)
		return (NULL);
	while (cmd[dc[0]])
	{
		if (cmd[dc[0]] != DOUBLE_QUOTE && cmd[dc[0]] != SIMPLE_QUOTE)
			n_cmd[dc[2]++] = cmd[dc[0]];
		else if ((cmd[dc[0]] == DOUBLE_QUOTE || cmd[dc[0]] == SIMPLE_QUOTE) && quote->p_bool[dc[1]] == 1)
		{
			n_cmd[dc[2]++] = cmd[dc[0]];
			dc[1]++;
		}
		else if ((cmd[dc[0]] == DOUBLE_QUOTE || cmd[dc[0]] == SIMPLE_QUOTE) && quote->p_bool[dc[1]] == 0)
			dc[1]++;
		dc[0]++;
	}
	return (n_cmd);
}

static void	ft_check_stat(t_quote *quote, char *cmd, int **st)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (cmd[i])
	{
		if (cmd[i] == DOUBLE_QUOTE || cmd[i] == SIMPLE_QUOTE)
		{
			if (i >= st[j][0] && i <= st[j][1])
			{
				quote->p_bool[k++] = 1;
				while (i++ <= st[j][1])
					if (cmd[i] == DOUBLE_QUOTE || cmd[i] == SIMPLE_QUOTE)
						quote->p_bool[k++] = 1;
				j++;
			}
			else
				k++;
		}
		i++;
	}
}

static int	ft_gen_quote_pos(t_shell *shell, t_quote *quote, char *cmd, int **states)
{
	if (ft_strichr(cmd, DOUBLE_QUOTE) == -1 && ft_strichr(cmd, SIMPLE_QUOTE) == -1)
		return (0);
	quote->len = ft_len_quote(cmd);
	if (quote->len == 1)
		return (0);
	quote->pos = ft_track((int *)ft_memalloc(sizeof(int) * quote->len), &(shell)->t_pars);
	quote->p_bool = ft_track((int *)ft_memalloc(sizeof(int) * quote->len), &(shell)->t_pars);
	if (!quote->p_bool || !quote->pos)
		return (0);
	ft_complete_tab_quote(quote, cmd, states);
	ft_track_quote(quote, quote->len);
	if (states)
		ft_check_stat(quote, cmd, states);
	int	i;

	i = 0;
	while (i < (int)quote->len)
	{
		printf("| %d |", quote->p_bool[i]);
		i++;
	}
	printf("\n");
	return (1);
}

/* @function remove quote of the string */ 
/* @char *cmd */
/* @return (int) */
char	*ft_remove_quote(t_shell *shell, char *cmd, int **states)
{
	t_quote	*quote;
	char	*n_cmd = NULL;

	printf("entre ft_quote  %s\n\n\n", cmd);
	quote = ft_track(ft_memalloc(sizeof(t_quote)), &(shell)->t_pars);
	if (!ft_gen_quote_pos(shell, quote, cmd, NULL))
		return (cmd);
	if (!states)
		n_cmd = ft_replace_cmd_without_state(shell, quote, cmd);
	ft_track_free(&(shell)->t_pars, cmd);
	return (n_cmd);
}
