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
# include <limits.h>
# include "../libft/include/libft.h"
# include "struct.h"

# if defined(__linux__) || defined(linux) || defined(__linux)
#  define MY_SIZE_T_MAX SIZE_MAX
# else
#  define MY_SIZE_T_MAX SIZE_T_MAX
# endif

/* function in lst_env.c */
t_env	*ft_create_envp(char *key, char *value, t_track *t);
t_env	*ft_last(t_env *lst);
void	ft_add_back(t_env **alst, t_env *ne);

/* function in get_envp.c */

/***************************************************************/
/*                           BULTIN                            */
/***************************************************************/

/* fucntion builtin env.c */
/* int		ft_env(t_shell *env); */

/* fucntion builtin export.c */
/* int		ft_export(t_shell *env, char *exptrt); */
/* int		ft_check_var(char *s1, char *s2, int c); */
/* int	ft_show_export(t_shell *env, char *export); */
/* char	*ft_export_syntax(char *str); */

/* fucntion builtin unset.c */
/* int		ft_unset(t_shell *env, char *unset); */

/* fucntion builtin exit.c */
void	ft_exit(t_shell *shell, int status);

/* fucntion builtin echo.c */
/* void	ft_echo(char **args); */

/* function conv lst to tab lst_to_tab.c*/
/* char	**ft_lst_to_tab(t_envp *lst); */
/* char	*ft_get_pwd(t_envp *lst); */

/* function alloc pwd for mini_shell in show_pwd.c*/ 
/* char	*ft_get_pwd(t_envp *lst); */


#endif

/* https://harm-smits.github.io/42docs/projects/minishell */
