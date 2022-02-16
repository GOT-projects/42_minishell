
#include "../../../includes/mini_shell.h"

static int	ft_catch_var(t_quote *quote, char *cmd)
{
	t_env	*node;
	size_t	i;
	int	ret;

	i = 0;
	ret = 0;
	while (cmd[i])
	{
		if (cmd[i] == '$')
		{
			
		}
		i++;
	}
	return (ret);
}

char	*ft_replace_var(t_shell *shell, char *cmd)
{
	char	*n_cmd;
	size_t	i;
	size_t	len;

	shell->quote = ft_track(ft_memalloc(sizeof(t_quote)), &(shell->t_pars));
	if (ft_strichr(cmd, '$') == -1)
		return (cmd);
	shell->quote->quote = TRUE;
	ft_init_quote(shell, shell->quote, cmd);
	if (!ft_catch_var(shell->quote, cmd))

	i = 0;

}
