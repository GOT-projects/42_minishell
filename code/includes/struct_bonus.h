/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges <aartiges@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 19:14:08 by aartiges &        #+#    #+#             */
/*   Updated: 2022/03/07 19:18:03 by aartiges         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_BONUS_H

# define STRUCT_BONUS_H

# include "includes.h"

typedef struct s_wild
{
	int		len;
	int		len_cmd;
	int		len_full;
	int		len_wild;
	int		c_dir;
	int		check;
	int		*p_bool;
	char	**full_dir;
}	t_wild;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}		t_env;

typedef struct s_quote
{
	int	*pos;
	int	*p_bool;
	int	len;
}	t_quote;

typedef struct s_var
{
	int		l_var;
	int		l_full;
	char	*n_cmd;
	char	**t_var;
	int		*p_bool;
}	t_var;

typedef enum e_priority
{
	BOOL,
	PIPE,
	REDIRECTION,
	SUB_SHELL,
	CMD
}	t_priority;

typedef enum e_redirection
{
	OUT_1,
	OUT_2,
	IN_1,
	IN_2
}	t_redirection;

typedef enum e_bool
{
	NONE,
	AND,
	OR
}	t_bool;

typedef struct s_node
{
	_Bool			root;
	t_priority		genre;
	t_redirection	type_redirection;
	t_bool			type_bool;
	char			**cmd;
	char			*to_parse;
	char			*file;
	struct s_node	*childs;
	struct s_node	*next;
	struct s_node	*lst_redir;
}	t_node;

typedef struct s_shell
{
	t_track	*t_env;
	t_track	*t_pars;
	t_env	*env;
	t_quote	*quote;
	int		last_exit_status;
	t_node	*operation;
}		t_shell;

#endif
