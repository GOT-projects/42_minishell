#include "../../includes/mini_shell.h"

/**
 * @brief function that take the command line with a correct syntax (prompt)
 * and create the tree of the execution of the command
 * 
 * @param shell the shell
 * @param line the command line
 * @return int 0 if success, 1 else
 */
int	ft_parse(t_shell *shell, char *line)
{
	shell->operation = ft_track(malloc(sizeof(t_operation)), &(shell->t_pars));
	if (!shell->operation)
		return (1);
	ft_bzero(shell->operation, sizeof(t_operation));
	shell->operation->root = true;
	shell->operation->to_parse = ft_track(ft_strtrim(line, SPACES),
			&(shell->t_pars));
	if (shell->operation->to_parse[ft_strlen(shell->operation->to_parse) - 1]
		== '|' && (ft_get_forgot_pipe(shell)
			|| ft_check_syntax(shell->operation->to_parse)))
		return (1);
	return (ft_construct_child(shell, shell->operation));
}
