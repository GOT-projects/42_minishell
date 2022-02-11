#ifndef STRUCT_H
# define STRUCT_H
# include "../libft/include/libft.h"

/* struct des pipe et des fdin et fdout */
/* typedef struct s_pipe */
/* { */
/* 	int		o_fdin; */
/* 	int		o_fdout; */
/* 	int		fdin; */
/* 	int		fdout; */
/* 	int		pfd[2]; */
/* 	int		pipefd[2]; */
/* 	pid_t	*pid; */
/* }		t_pipe; */

/* liste chainé des variable env */
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}		t_env;

/* structure generale */
typedef struct s_shell
{
	t_track		*t_env;
	t_track		*t_pars;
	t_env		*env;
	int			last_exit_status; //$?
}		t_shell;

typedef	enum e_priority
{
	BOOL,
	PIPE,
	REDIRECTION
}	t_priority;

typedef	enum e_redirection
{
	OUT_1,
	OUT_2,
	IN_1,
	IN_2
}	t_redirection;

typedef	enum e_bool
{
	AND,
	OR
}	t_bool;

typedef struct s_operaration
{
	t_priority			genre;
	t_redirection		type_redirection;
	t_bool				type_bool;
	char				**cmd;
	char				*to_parse;
	struct s_operation	*next_op;
	struct s_operation	*lst_op;
}	t_operation;

#endif
