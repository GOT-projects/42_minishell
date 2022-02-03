#ifndef STRUCT_H
# define STRUCT_H
# include "../libft/include/libft.h"

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
}		t_shell;

#endif
