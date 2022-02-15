#include "../../../includes/mini_shell.h"

int	ft_get_heredoc(t_shell *shell, t_operation *redir)
{
	char	*heredoc;
	char	*new_file;
	size_t	i;
	size_t	size;

	new_file = NULL;
	heredoc = readline("heredoc > ");
	while (heredoc && !ft_strcmp(heredoc, redir->file))
	{
		new_file = realloc(new_file,
				(ft_strlen(heredoc) + ft_strlen(new_file) + 2) * sizeof(char));
		size = ft_strlen(new_file);
		i = size;
		
		free(heredoc);
		heredoc = readline("heredoc > ");
	}
	ft_track_free(&(shell->t_pars), redir->file);
	redir->file = new_file;
	return (0);
}