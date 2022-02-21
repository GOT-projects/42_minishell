#ifndef MINI_SHELL_H

# define MINI_SHELL_H
///////////////////////////////////////////////////////////////////////////////////////////
# define BONUS

# include "includes.h"
# include "define_common.h"
# ifdef BONUS
#  include "struct_bonus.h"
# else
#  include "struct.h"
# endif

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
int		ft_exec_cmd(t_shell *shell, char **cmd);
int		ft_exec(t_shell *shell, t_node *op);

//pipe

void	ft_free_pipes(int ***pipes, size_t nb_pipes);
int		ft_error_fork_of_pipe(pid_t *pids, size_t i, int ***pipes,
			size_t nb_childs);
int		ft_end_of_pipe(t_shell *shell, pid_t *pids, int ***pipes,
			size_t nb_childs);
int		ft_exec_pipe(t_shell *shell, t_node *op);

// redir

int		ft_exec_redir(t_shell *shell, t_node *op);
int		ft_apply_output_redirection(t_node *redir);
int		ft_apply_input_redirection(t_node *redir);
void	ft_close_pipe(int pipes[2]);

/***************************************************************/
/*                         PARSING                             */
/***************************************************************/

// utils
_Bool	ft_is_shell_var(char const *var);
_Bool	ft_str_start_with(char *str, char *to_find);
int		ft_pars_quote(char c, char *quote);
void	ft_free_2d(char **array);
_Bool	ft_is_shell_var(char const *var);

// transform
int		ft_free2d_index(char **split, size_t index);
char	*create_string(char *str, size_t start, size_t end);
char	**ft_split_str(char const *s, char *to_find);
char	*ft_remove_quote(t_shell *shell, char *cmd, int **states);
int		ft_c_quote(int c);
/* int		ft_init_quote(t_shell *shell, t_quote *quote, char *cmd); */
int		**ft_replace_var(t_shell *shell, char **cmd);
int		ft_len_quote(char *cmd);
void	ft_complete_tab_quote(t_quote *quote, char *cmd);
void	ft_while_quote(t_quote *quote, int *d, int **st, char *cmd);
void	ft_set_quote(t_quote *quote, int *d);
void	ft_set_st(int **st, int j);
int		ft_get_len_var(char *cmd);
int		ft_get_nb_var(char *cmd);
int		ft_get_full_len_var(t_shell *shell, t_var *var);
int		ft_get_full_len_var(t_shell *shell, t_var *var);

// syntax
int		ft_check_syntax(char *line);
int		ft_check_syntax_prompt(char *line);

// PROMPT
int		ft_get_forgot_cmd(t_shell *shell);
int		ft_get_heredoc(t_shell *shell, t_node *redir);

// tree
void	ft_op_add_back(t_node **ops, t_node *node);
size_t	ft_op_bro_size(t_node *childs);
t_node	*ft_get_new_node(t_shell *shell);
int		ft_construct_cmd(t_shell *shell, t_node *current);
int		ft_construct_pipe(t_shell *shell, t_node *current);
int		ft_construct_redirection(t_shell *shell, t_node *current);
int		ft_construct_child(t_shell *shell, t_node *current);

//parsing
int		ft_parse(t_shell *shell, char *line);

/***************************************************************/
/*                         SIGNALS                             */
/***************************************************************/

/*
Ctrl+C - SIGINT Interruption (ctrl-C)	Terminaison
Ctrl+\ - SIGQUIT 	Interruption forte (ctrl-\)	Terminaison + core dump
*/

void	exec_mode_sub_process(void);
void	exec_mode(void);
void	interactive_mode(void);

/***************************************************************/
/*                           DEBUG                             */
/***************************************************************/

void	debug_tree(t_node *op, int level);

#endif
