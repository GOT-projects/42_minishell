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
# include "struct.h"

/* function in lst_env.c */
t_envp	*ft_create_envp(char *str, t_track *t);
t_envp	*ft_last(t_envp *lst);
void	ft_add_back(t_envp **alst, t_envp *ne);

/* function in get_envp.c */
int		ft_get_env(t_shell *env, t_track *t, char **envp);
int		ft_get_export(t_shell *env, t_track *t, char **envp);
int		ft_sort_export(t_envp *export);
int		ft_check_lst(t_envp *lst, char *s);

/***************************************************************/
/*                           BULTIN                            */
/***************************************************************/

/* fucntion builtin env.c */
int		ft_env(t_shell *env);

/* fucntion builtin export.c */
int		ft_export(t_shell *env, char *exptrt);
int		ft_check_var(char *s1, char *s2, int c);
void	ft_show_export(t_shell *env);
char	*ft_export_syntax(char *str);

/* fucntion builtin unset.c */
int		ft_unset(t_shell *env, char *unset);

/* fucntion builtin exit.c */
void	ft_exit(t_shell *shell, int status);

/* fucntion builtin echo.c */
void	ft_echo(char **args);

#endif

/* https://harm-smits.github.io/42docs/projects/minishell */
