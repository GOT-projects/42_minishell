#include "../../../includes/mini_shell.h"

static int	ft_join_heredoc(char **new_file, char *heredoc)
{
	size_t	i;
	size_t	size;
	char	*tmp;

	tmp = *new_file;
	*new_file = realloc(*new_file,
			(ft_strlen(*new_file) + ft_strlen(heredoc) + 2) * sizeof(char));
	if (!(*new_file))
	{
		free(tmp);
		return (1);
	}
	size = ft_strlen(*new_file);
	i = size;
	while (heredoc[i - size])
	{
		(*new_file)[i] = heredoc[i - size];
		++i;
	}
	(*new_file)[i++] = '\n';
	(*new_file)[i] = '\0';
	return (0);
}

int	ft_get_heredoc(t_shell *shell, t_operation *redir)
{
	char	*heredoc[2];
	char	*new_file;

	new_file = NULL;
	if (!ft_remove_quote(shell, redir->file))
		return (1);
	printf ("test\n");
	heredoc[0] = ft_join("heredoc %s > ", redir->file);
	heredoc[1] = readline(heredoc[0]);
	while (heredoc[1] && !ft_strcmp(heredoc[1], redir->file))
	{
		if (ft_join_heredoc(&new_file, heredoc[1]))
		{
			free(heredoc[0]);
			free(heredoc[1]);
			free(new_file);
			return (1);
		}
		free(heredoc[1]);
		heredoc[1] = readline(heredoc[0]);
	}
	free(heredoc[0]);
	ft_track_free(&(shell->t_pars), redir->file);
	redir->file = new_file;
	ft_track(redir->file, &(shell->t_pars));
	return (0);
}
