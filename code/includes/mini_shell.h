/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges & jmilhas <x@student.42lyon.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 22:42:23 by aartiges          #+#    #+#             */
/*   Updated: 2022/03/07 21:47:00 by aartiges &       ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H

# define MINI_SHELL_H

# include "includes.h"
# include "define_common.h"
# ifndef BONUS
#  include "struct.h"
# else
#  include "struct_bonus.h"

_Bool	ft_check_parenthese_post_pars(char *line);
_Bool	ft_check_parenthese_pre_pars(char *line);
char	**ft_add_dir_in_wild(t_wild *wd, t_shell *shell, char **cmd);
char	**ft_wildcard(t_shell *shell, char **cmd, int *wd);
char	*ft_alloc_dir(t_wild *wd, int *d);
int		*ft_checker_wildcard(t_shell *shell, char **cmd);
int		ft_all(t_wild *wd);
int		ft_ch_wd_var(t_shell *shell, char *cmd);
int		ft_check_dir_cmd(t_wild *wd, char *cmd);
int		ft_check_wild(char **cmd, int *wd);
int		ft_check_wildcard(char **cmd);
int		ft_construct_bool(t_shell *shell, t_node *current);
int		ft_construct_subshell(t_shell *shell, t_node *current);
int		ft_end_wd(char *wd, char *cmd);
int		ft_exec_bool(t_shell *shell, t_node *op);
int		ft_exec_sub_shell(t_shell *shell, t_node *op);
int		ft_get_len_p_bool(t_wild *wd);
int		ft_get_wildcard(char *wild, char *cmd);
int		ft_len_dir(char *p_dir);
int		ft_pars_parenthese(char c, int *parenthese);
int		ft_tablen(char **t);
void	ft_free_add(t_shell *shell, t_wild *wd, char **cmd);
void	ft_get_dir(char **full, char *p_dir);
void	ft_get_dir_hid(char **full, char *p_dir);
void	ft_syntax_error_bonus(int state);

# endif

/***************************************************************/
/*                             ENV                             */
/***************************************************************/

/* function in lst_env.c */
t_env	*ft_create_envp(char *key, char *value, t_track **t);
t_env	*ft_last(t_env *lst);
void	ft_add_back(t_env **alst, t_env *ne);

/* function in get_utils.c */
char	*ft_get_env_val(t_env *node_var);
int		ft_export_add(t_shell *shell, char *key, char *new_val);
t_env	*ft_get_env_key(t_env *lst, const char *key);
t_env	*ft_replace_node(t_env *node, char *value, t_track **t);
void	ft_init_oldpwd(t_shell *shell);

/* function in ft_get_env.c */
char	**ft_get_path(t_shell *shell);
char	**ft_lst_to_tab(t_shell *shell);
void	ft_init_env(t_shell *shell, char **ev);
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

// echo
int		ft_echo(char **args);

// cd
int		ft_cd(t_shell *shell, char **paths);
int		ft_get_pwd(char *str);
size_t	ft_nb_args(char **args);

// pwd
int		ft_pwd(void);

/***************************************************************/
/*                            EXEC                             */
/***************************************************************/

// Simple exec
int		ft_error_exit_process(char *prg_name, int status);
int		ft_exec(t_shell *shell, t_node *op);
int		ft_exec_cmd(t_shell *shell, char **cmd);
int		ft_exec_prg(t_shell *shell, char **cmd);
void	ft_prg_error_research_path(char **cmd, int error_research);

//pipe
int		ft_error_fork_of_pipe(pid_t *pids, size_t i, int ***pipes,
			size_t nb_childs);
int		ft_end_of_pipe(t_shell *shell, pid_t *pids, int ***pipes,
			size_t nb_childs);
int		ft_error_create_pipe(pid_t *pids, size_t i, int ***pipes,
			size_t nb_childs);
int		ft_exec_pipe(t_shell *shell, t_node *op);
void	ft_free_pipes(int ***pipes, size_t nb_pipes);

// redir
int		ft_apply_input_redirection(t_node *redir);
int		ft_apply_output_redirection(t_node *redir);
int		ft_exec_redir(t_shell *shell, t_node *op);
void	ft_close_pipe(int pipes[2]);

/***************************************************************/
/*                         PARSING                             */
/***************************************************************/

// utils
_Bool	ft_is_shell_var(char const *var);
_Bool	ft_is_var(char const *var);
_Bool	ft_str_start_with(char *str, char *to_find);
int		ft_pars_quote(char c, char *quote);
void	ft_free_2d(char **array);

// transform
char	**ft_split_str(char const *s, char *to_find);
char	*create_string(char *str, size_t start, size_t end);
char	*ft_remove_quote(t_shell *shell, char *cmd, int **states);
int		ft_c_quote(int c);
int		ft_free2d_index(char **split, size_t index);

/* int		ft_init_quote(t_shell *shell, t_quote *quote, char *cmd); */
char	**ft_remove_empty_cmd(char **cmd, int index);
int		**ft_replace_var(t_shell *shell, char **cmd);
int		ft_get_full_len_var(t_shell *shell, t_var *var);
int		ft_get_full_len_var(t_shell *shell, t_var *var);
int		ft_get_len_var(char *cmd);
int		ft_get_nb_var(char *cmd);
int		ft_len_quote(char *cmd);
void	ft_complete_tab_quote(t_quote *quote, char *cmd);
void	ft_set_quote(t_quote *quote, int *d, int c);
void	ft_set_st(int **st, int j);
void	ft_while_quote(t_quote *quote, int *d, int **st, char *cmd);
int		**ft_catch_dollar_var(t_var *var, t_shell *shell, int **st, int **d);

// syntax
int		ft_check_syntax(char *line);
int		ft_check_syntax_prompt(char *line);

// PROMPT
char	*ft_create_str_read_line(t_shell *shell);
int		ft_get_forgot_cmd(t_shell *shell);
int		ft_get_heredoc(t_shell *shell, t_node *redir);

// tree
int		ft_construct_child(t_shell *shell, t_node *current);
int		ft_construct_cmd(t_shell *shell, t_node *current);
int		ft_construct_pipe(t_shell *shell, t_node *current);
int		ft_construct_redirection(t_shell *shell, t_node *current);
size_t	ft_op_bro_size(t_node *childs);
t_node	*ft_get_new_node(t_shell *shell);
void	ft_op_add_back(t_node **ops, t_node *node);

//parsing
int		ft_parse(t_shell *shell, char *line);

/***************************************************************/
/*                         SIGNALS                             */
/***************************************************************/

/*
Ctrl+C - SIGINT Interruption (ctrl-C)	Terminaison
Ctrl+\ - SIGQUIT 	Interruption forte (ctrl-\)	Terminaison + core dump
*/

void	exec_mode(void);
void	exec_mode_sub_process(void);
void	interactive_mode(void);

/***************************************************************/
/*                           DEBUG                             */
/***************************************************************/

void	debug_print_tabs(size_t level);
void	debug_print_pipe(t_node *op, size_t level);
void	debug_print_redir(t_node *op, size_t level);
void	debug_print_cmd(t_node *op, size_t level);
void	debug_tree(t_node *op, int level);

#endif
