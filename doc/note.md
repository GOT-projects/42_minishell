(echo 1 && sleep 3 && echo 2) | cat -e
grep yes << o

# TODO

trim exec
check signal ctl \

t_envp	*ft_get_env_key(t_envp *env, char *key); //TODO
char	*ft_get_env_val(t_envp *var_env); //TODO
int		ft_export_replace(char *key, char *new_val);
//suppr elem -- free rm track -- (elem)
//int		ft_export_replace("OLDPWD", path);
# Priorities

1. quotes
    - extraire les string (traduire les variable bash si necessaire)
    - split tout ce qui n'etait pas entre quotes
        - appliquer le wildcards * *bonus*
*Note : toutes char\* seront soit une commande / flag / arg, soit un opétateur*
3. parenthese *bonus*
    - Séparer de façon récursive (parenthèses dans des parenthèses) les commandes
4. operator bool *bonus*
    - 
5. pipe
6. redirection


/!\/!\/!\/!\/!\/!\/!\
debut de chaque fork add PWD var
/!\/!\/!\/!\/!\/!\/!\


-------------


readline:   lit le prompt et renvoi
rl_clear_history: void rl_clear_history (void)
rl_on_new_line:  int rl_on_new_line (void)
    Tell the update functions that we have moved onto a new (empty) line, usually after outputting a newline
rl_replace_line: void rl_replace_line (const char *text, int clear_undo)
    Replace the contents of rl_line_buffer with text. The point and mark are preserved, if possible. If clear_undo is non-zero, the undo list associated with the current line is cleared.
rl_redisplay: void rl_redisplay (void)
    Change what's displayed on the screen to reflect the current contents of rl_line_buffer.
add_history(char *rl)


access: check permission / exist
stat: 
lstat:
fstat:
unlink: suppr file


isatty: is a term (redir / pipe)
ttyname:
ttyslot: ??????

ioctl:
getenv:

tcsetattr:
tcgetattr:
tgetent:
tgetflag:
tgetnum:
tgetstr:
tgoto:
tputs:


-----------------------
```c

#define OP_CMD		0b1
#define OP_SUB		0b10
#define OP_AND		0b100
#define OP_OR		0b1000
#define OP_PIPE		0b10000
#define OP_REDIR	0b100000

typedef struct  s_operation
{
	char				op;
	char				**cmd;
	struct s_operation	*son1;
	struct s_operation	*son2;
}	t_node;

void	justdoit(t_shell *shell, t_node *tree)
{
	if (tree->op == OP_CMD)
		exec(cmd)

}


```
