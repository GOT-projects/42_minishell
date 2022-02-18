#include "../../../includes/mini_shell.h"

static size_t	ft_len_quote_with_states(char *cmd, size_t **states)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = 0;
	len = 0;
	while (cmd[i])
	{
		if ((states[j]) && (cmd[i] == DOUBLE_QUOTE || cmd[i] == SIMPLE_QUOTE)
			&& i < states[j][0])
			len++;
		if ((!states[j]) && (cmd[i] == DOUBLE_QUOTE || cmd[i] == SIMPLE_QUOTE))
			len++;
		if (!states[j] && i >= states[j][0])
		{
			while (i < states[j][1])
				i++;
			j++;
		}
		i++;
	}
	return (len);
}

static size_t	ft_len_quote(char *cmd, size_t **states)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	if (!states)
	{
		while (cmd[i])
		{
			if (cmd[i] == DOUBLE_QUOTE || cmd[i] == SIMPLE_QUOTE)
				len++;
			i++;
		}
	}
	else
		len = ft_len_quote_with_states(cmd, states);
	return len;
}

static void	ft_complete_tab_quote_states(t_quote *quote, char *cmd, size_t **st)
{
	size_t	i;
	size_t	j;
	size_t	k;

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

static void	ft_complete_tab_quote(t_quote *quote, char *cmd, size_t **states)
{
	size_t	i;
	size_t	j;

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

static void	ft_track_quote(t_quote *quote, size_t len)
{
	size_t	i;
	size_t	state;

	i = 0;
	state = 0;
	while (i < len)
	{
		if (state && state == quote->pos[i] && i <= len)
		{
			quote->p_bool[i++] = 0;
			state = 0;
		}
		else if (!state && i <= len)
		{
			state = quote->pos[i];
			quote->p_bool[i++] = 0;
		}
		if (state && i < len)
			while (quote->pos[i] != state && i <= len)
				quote->p_bool[i++] = 1;	
	}
}

static char	*ft_replace_cmd_without_state(t_shell *shell, t_quote *quote, char *cmd)
{
	char	*n_cmd;
	size_t	dc[3];

	size_t	i;
	i = 0;
	while (i < quote->len)
	{
		printf("pos |%lu|%lu| true\n", quote->pos[i], quote->p_bool[i]);
		i++;
	}
	ft_bzero(dc, sizeof(size_t) * 3);
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
		printf("n_cmd %s\n", n_cmd);
		dc[0]++;
	}
	return (n_cmd);
}

static int	ft_gen_quote_pos(t_shell *shell, t_quote *quote, char *cmd, size_t **states)
{
	size_t	len;

	if (ft_strichr(cmd, DOUBLE_QUOTE) == -1 && ft_strichr(cmd, SIMPLE_QUOTE) == -1)
		return (0);
	len = ft_len_quote(cmd, states);
	quote->len = len;
	quote->pos = ft_track((size_t *)ft_memalloc(sizeof(size_t) * len), &(shell)->t_pars);
	quote->p_bool = ft_track((size_t *)ft_memalloc(sizeof(size_t) * len), &(shell)->t_pars);
	if (!quote->p_bool || !quote->pos)
		return (0);
	ft_complete_tab_quote(quote, cmd, states);
	ft_track_quote(quote, len);
	printf("%s track\n", cmd);
	return (1);
}

/* @function remove quote of the string */ 
/* @char *cmd */
/* @return (int) */
char	*ft_remove_quote(t_shell *shell, char *cmd, int **states)
{
	t_quote	*quote;
	char	*n_cmd = NULL;

	quote = ft_track(ft_memalloc(sizeof(t_quote)), &(shell)->t_pars);
	if (!ft_gen_quote_pos(shell, quote, cmd, NULL))
		return (cmd);
	if (!states)
		n_cmd = ft_replace_cmd_without_state(shell, quote, cmd);
	ft_track_free(&(shell)->t_pars, cmd);
	return (n_cmd);
}
