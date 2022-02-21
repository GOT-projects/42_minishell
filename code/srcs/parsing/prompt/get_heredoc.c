/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges & jmilhas <x@student.42lyon.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 20:25:48 by aartiges &        #+#    #+#             */
/*   Updated: 2022/02/21 20:25:52 by aartiges &       ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mini_shell.h"

/**
 * @brief each time the key enter is press this function concat the old content
 * with the new line
 * 
 * @param new_file the old content
 * @param heredoc the new content
 * @return int 0 at success, else > 0
 */
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
	size = 0;
	if (tmp)
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

/**
 * @brief free the array heredoc
 * 
 * @param heredoc the array
 */
static void	ft_free_heredoc(char *heredoc[2])
{
	free(heredoc[0]);
	free(heredoc[1]);
}

/**
 * @brief do the heredoc
 * 
 * @param shell the shell
 * @param redir the redirection, at the start contain the delimitor of the
 * heredoc
 * @return int 0 at success, else 1
 */
int	ft_get_heredoc(t_shell *shell, t_node *redir)
{
	char	*heredoc[2];
	char	*new_file;

	new_file = NULL;
	redir->file = ft_remove_quote(shell, redir->file, NULL);
	if (!redir->file)
		return (1);
	heredoc[0] = ft_join("heredoc %s > ", redir->file);
	heredoc[1] = readline(heredoc[0]);
	while (heredoc[1] && ft_strcmp(heredoc[1], redir->file))
	{
		if (ft_join_heredoc(&new_file, heredoc[1]))
		{
			ft_free_heredoc(heredoc);
			free(new_file);
			return (1);
		}
		free(heredoc[1]);
		heredoc[1] = readline(heredoc[0]);
	}
	ft_free_heredoc(heredoc);
	ft_track_free(&(shell->t_pars), redir->file);
	redir->file = new_file;
	ft_track(redir->file, &(shell->t_pars));
	return (0);
}
