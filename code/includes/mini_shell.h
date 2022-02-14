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

# define ERR_404_EXEC	127
# define ERR_403_EXEC	126

# define ENV_PWD		"PWD"
# define ENV_PWD_OLD	"OLDPWD"

# define SPACES			" \t\n\r\v\f"

# define CHECK_OK			0
# define EMPTY				0b1
# define CHECK_TEXT			0b10
# define CHECK_PIPE			0b100
# define CHECK_RED_APPEND	0b1000
# define CHECK_RED_CREATE	0b10000
# define CHECK_RED_HR_DOC	0b100000
# define CHECK_RED_INPUT	0b1000000
# define CHECK_QUOTE		0b10000000

/***************************************************************/
/*                             ENV                             */
/***************************************************************/

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
int		ft_exit(t_shell *shell, char **status);

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

/***************************************************************/
/*                            EXEC                             */
/***************************************************************/

// Simple exec
int		ft_exec_prg(t_shell *shell, char **cmd);
int		ft_error_exit_process(char *prg_name, int status);
void	ft_prg_error_research_path(char **cmd, int error_research);

/***************************************************************/
/*                         PARSING                             */
/***************************************************************/

// utils
_Bool	ft_str_start_with(char *str, char *to_find);
int		ft_pars_quote(char c, char *quote);
void	ft_free_2d(char **array);

int		ft_free2d_index(char **split, size_t index);
char	*create_string(char *str, size_t start, size_t end);
char	**ft_split_str(char const *s, char *to_find);

// syntax
int		ft_check_syntax(char *line);
int		ft_check_syntax_prompt(char *line);

// PROMPT
int		ft_get_forgot_pipe(t_shell *shell);

// tree
void	ft_op_add_back(t_operation **ops, t_operation *node);
t_operation		*ft_get_new_node(t_shell *shell);
int		ft_construct_cmd(t_shell *shell, t_operation *current);
t_operation	*ft_construct_pipe(t_shell *shell, t_operation *current);
t_operation	*ft_construct_redirection(t_shell *shell, t_operation *current);
int		ft_construct_child(t_shell *shell, t_operation *current);


//parsing
int		ft_parse(t_shell *shell, char *line);

/***************************************************************/
/*                         SIGNALS                             */
/***************************************************************/

/*
Ctrl+C - SIGINT Interruption (ctrl-C)	Terminaison
Ctrl+\ - SIGQUIT 	Interruption forte (ctrl-\)	Terminaison + core dump
*/

void	interactive_mode(void);

#endif