#include "../../../includes/mini_shell.h"

int	ft_get_heredoc(t_shell *shell, t_operation *redir)
{
	char	*heredoc;
	char	*new_file;
	size_t	i;

	new_file = NULL;
	heredoc = readline("heredoc > ");
	while (heredoc && !ft_strcmp(heredoc, redir->file))
	{
		new_file = realloc(new_file,
				(ft_strlen(heredoc) + ft_strlen(new_file) + 2) * sizeof(char));
		i = ft_strlen(new_file);

		free(heredoc);
		heredoc = readline("heredoc > ");
	}
	return (0);
}