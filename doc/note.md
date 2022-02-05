(echo 1 && sleep 3 && echo 2) | cat -e
grep yes << o
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
}	t_operation;

void	justdoit(t_shell *shell, t_operation *tree)
{
	if (tree->op == OP_CMD)
		exec(cmd)

}


```