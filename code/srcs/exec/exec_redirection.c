/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges <aartiges@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 19:52:32 by aartiges &        #+#    #+#             */
/*   Updated: 2022/03/07 19:17:03 by aartiges         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"
/**
 * @brief function that save the stdin and the stdout int the array std
 * 
 * @param std the array that contain a duplicat of the original stdin/stdout
 * @return int 0 at success, else > 0
 */
static int	ft_save_stdin_stdout(int std[2])
{
	std[READ] = dup(READ);
	if (std[READ] == -1)
	{
		perror("redirection: dup stdin");
		return (1);
	}
	std[WRITE] = dup(WRITE);
	if (std[WRITE] == -1)
	{
		perror("redirection: dup stdout");
		close(std[READ]);
		return (1);
	}
	return (0);
}

/**
 * @brief function that restore the stdin and the stdout (like at the start)
 * 
 * @param std the array that contain a duplicat of the original stdin/stdout
 * @return int 0 at success, else > 0
 */
static int	ft_restore_stdin_stdout(int std[2])
{
	if (dup2(std[READ], READ) == -1)
	{
		ft_close_pipe(std);
		perror("redirection: dup2 stdin");
		return (1);
	}
	if (dup2(std[WRITE], WRITE) == -1)
	{
		ft_close_pipe(std);
		perror("redirection: dup2 stdout");
		return (1);
	}
	ft_close_pipe(std);
	return (0);
}

/**
 * @brief apply all type of redirection
 * 
 * @param redir the actual redirection
 * @return ** int 0 at success, else > 0
 */
static int	ft_apply_redirections(t_node *redir)
{
	while (redir)
	{
		if (redir->type_redirection == OUT_1
			|| redir->type_redirection == OUT_2)
		{
			if (ft_apply_output_redirection(redir))
				return (1);
		}
		else
		{
			if (ft_apply_input_redirection(redir))
				return (1);
		}
		redir = redir->next;
	}
	return (0);
}

/**
 * @brief apply all the redirections
 * 
 * @param shell the shell
 * @param op the node of redirection
 * @return int 0 at success, else > 0
 */
int	ft_exec_redir(t_shell *shell, t_node *op)
{
	int	std[2];

	if (ft_save_stdin_stdout(std))
		return (1);
	if (ft_apply_redirections(op->lst_redir))
		return (1);
	op = op->childs;
	while (op)
	{
		ft_exec(shell, op);
		op = op->next;
	}
	if (ft_restore_stdin_stdout(std))
		return (1);
	return (0);
}
