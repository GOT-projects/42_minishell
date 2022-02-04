#ifndef STRUCT_H
# define STRUCT_H
# include "../libft/include/libft.h"

/* struct des pipe et des fdin et fdout */
typedef struct s_pipe
{
	int		o_fdin;
	int		o_fdout;
	int		fdin;
	int		fdout;
	int		pfd[2];
	int		pipefd[2];
	pid_t	*pid;
}		t_pipe;

/* liste chainé des variable env */
typedef struct s_envp
{
	char			*envp;
	struct s_envp	*next;
	struct s_envp	*prev;
}		t_envp;

/* structure generale */
typedef struct s_shell
{
	t_track		*t_env;
	t_track		*t_pars;
	t_envp		*envp;
	t_envp		*export;
	t_pipe		*pipe;
}		t_shell;

#endif
