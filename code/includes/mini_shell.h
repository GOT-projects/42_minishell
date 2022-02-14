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

# define ENV_PWD		"PWD"
# define ENV_PWD_OLD	"OLDPWD"

/* function in lst_env.c */
t_env	*ft_create_envp(char *key, char *value, t_track **t);
t_env	*ft_last(t_env *lst);
void	ft_add_back(t_env **alst, t_env *ne);

/* function in get_utils.c */
t_env	*ft_get_env_key(t_env *lst, const char *key);
char	*ft_get_env_val(t_env *node_var);
t_env	*ft_replace_node(t_env *node, char *value, t_track **t);
int		ft_export_add(t_shell *shell, char *key, char *new_val);

/* function in ft_get_env.c */ 
void	ft_init_env(t_shell *shell, char **ev);
char	**ft_get_path(t_shell *shell);
char	**ft_lst_to_tab(t_shell *shell);
void	ft_sort_env(t_env *lst);

/***************************************************************/
/*                           BULTIN                            */
/***************************************************************/

/* fucntion builtin env.c */
int		ft_env(t_shell *env);

/* fucntion builtin export.c */
int		ft_export(t_shell *env, char **exp);

/* fucntion builtin unset.c */
int		ft_unset(t_shell *env, char **unset);

/* fucntion builtin exit.c */
void	ft_exit(t_shell *shell, int status);

/* fucntion builtin echo.c */
/* void	ft_echo(char **args); */

/* function conv lst to tab lst_to_tab.c*/
/* char	**ft_lst_to_tab(t_envp *lst); */

// echo
int		ft_echo(char **args);

// cd
size_t	ft_nb_args(char **args);
int		ft_get_pwd(char *str);
int		ft_cd(t_shell *shell, char **paths);

// pwd
int		ft_pwd(void);

#endif
