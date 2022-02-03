#ifndef MINI_SHELL_H
# define MINI_SHELL_H
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <dirent.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <sys/types.h>
# include <sys/ioctl.h>
# include <sys/uio.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/include/libft.h"

/* function in lst_env.c */
t_envp	*ft_create_envp(char *str, t_track *t);
t_envp	*ft_last(t_envp *lst);
void	ft_add_back(t_envp **alst, t_envp *ne);

/* function in get_envp.c */
t_bool	ft_get_env(t_env *env, t_track *t,char **envp);
t_bool	ft_get_export(t_env *env, t_track *t, char **envp);
t_bool	ft_sort_export(t_envp *export);

/* fucntion builtin env.c */
t_bool	ft_env(t_env *env);

/* fucntion builtin export.c */
t_bool	ft_export(t_env *env, char *export);
t_bool	ft_check_var(char *s1, char *s2, int c);
void	ft_show_export(t_env *env);
char	*ft_export_syntax(char *str);

/* fucntion builtin unset.c */
t_bool	ft_unset(t_env *env, char *unset);


#endif


/* https://harm-smits.github.io/42docs/projects/minishell */
