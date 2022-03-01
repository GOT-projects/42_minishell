#include "includes/mini_shell.h"
#define WRITE_END 1
#define READ_END 0

int main(int argc, char const *argv[])
{
	char *test = NULL;
	test = readline("saisit: ");
	printf("%s\n", test);
	printf("%p\n", test);
	printf("%d\n", test[0] == '\0');
	add_history(test);
	free(test);
	test = readline("saisit: ");
	printf("%p\n", test);
	printf("%s\n", test);
	printf("%c\n", test);
	add_history(test);
	free(test);
	rl_clear_history();
	return 0;
}


/*
void free_tab(char **t)
{
	int i;
	i = 0;
	while (t[i])
		free(t[i++]);
	free(t);
}

int main(int argc, char const *argv[], char **env)
{
	pid_t pid;
	int fd[2];

	pipe(fd);
	pid = fork();
	char *test = ft_split("ls -l", ' ');
	char *test2 = ft_split("wc -l", ' ');

	if(pid==0)
	{
		dup2(fd[WRITE_END], STDOUT_FILENO);
		close(fd[READ_END]);
		close(fd[WRITE_END]);
		execve("/bin/ls", test, env);
		fprintf(stderr, "Failed to execute '%s'\n", "ls");
		exit(1);
	}
	else
	{ 
		pid=fork();

		if(pid==0)
		{
			dup2(fd[READ_END], STDIN_FILENO);
			close(fd[WRITE_END]);
			close(fd[READ_END]);
			execve("/usr/bin/wc", test2, env);
			fprintf(stderr, "Failed to execute '%s'\n", "cat");
			exit(1);
		}
		else
		{
			int status;
			close(fd[READ_END]);
			close(fd[WRITE_END]);
			waitpid(pid, &status, 0);
		}
	}
	free_tab(test);
	free_tab(test2);
	return 0;
}
*/