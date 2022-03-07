/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges <aartiges@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 19:47:37 by aartiges &        #+#    #+#             */
/*   Updated: 2022/03/07 19:13:59 by aartiges         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

/**
 * @brief close the 2 fildes of the pipe
 * 
 * @param pipes the pipe
 */
void	ft_close_pipe(int pipes[2])
{
	if (pipes)
	{
		close(pipes[READ]);
		close(pipes[WRITE]);
	}
}

/**
 * @brief the code of the sub process that write the heredoc in the pipe
 * 
 * @param pipes the pipe
 * @param redir the redirection that contain the string to pipe
 */
static void	ft_heredoc_fork(int pipes[2], t_node *redir)
{
	exec_mode_sub_process();
	close(pipes[READ]);
	if (dup2(pipes[WRITE], WRITE) == -1)
	{
		perror("redirection: input file: redirection");
		exit(1);
	}
	ft_putstr_fd(redir->file, pipes[WRITE]);
	close(pipes[WRITE]);
	exit(0);
}

/**
 * @brief function that create the process to do the redirection heredoc
 * 
 * @param redir the redirection
 * @return int 0 at success, else > 0
 */
static int	ft_apply_heredoc(t_node *redir)
{
	pid_t	pid;
	int		pipes[2];

	if (pipe(pipes) == -1)
	{
		perror("pipe redirection");
		return (1);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork redirection");
		ft_close_pipe(pipes);
		return (1);
	}
	else if (pid == 0)
		ft_heredoc_fork(pipes, redir);
	if (dup2(pipes[0], 0) == -1)
	{
		perror("redirection: input file: redirection");
		ft_close_pipe(pipes);
		return (1);
	}
	ft_close_pipe(pipes);
	return (0);
}

/**
 * @brief function that apply the redirection (in input ex:< <<)
 * 
 * @param redir the redirection
 * @return int 0 if success, else > 0
 */
int	ft_apply_input_redirection(t_node *redir)
{
	int		fd;

	if (redir->type_redirection == IN_1)
	{
		fd = open(redir->file, O_RDONLY);
		if (fd < 0)
		{
			perror(redir->file);
			return (1);
		}
		if (dup2(fd, READ) == -1)
		{
			perror("redirection: input file: redirection");
			return (1);
		}
		close(fd);
	}
	else
	{
		if (ft_apply_heredoc(redir))
			return (1);
	}
	return (0);
}

/**
 * @brief function that apply the redirection (in output ex:< <<)
 * 
 * @param redir the redirection
 * @return int 0 if success, else > 0
 */
int	ft_apply_output_redirection(t_node *redir)
{
	int	fd;

	if (redir->type_redirection == OUT_1)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror(redir->file);
		return (1);
	}
	if (dup2(fd, WRITE) == -1)
	{
		perror("redirection: output file: redirection");
		return (1);
	}
	return (0);
}
