#include "includes/mini_shell.h"
#define WRITE_END 1
#define READ_END 0

int main(int argc, char const *argv[], char **env)
{
	pid_t pid;
	int fd[2];

	pipe(fd);
	pid = fork();
	char *test = malloc(15);

	if(pid==0)
	{
		dup2(fd[WRITE_END], STDOUT_FILENO);
		close(fd[READ_END]);
		close(fd[WRITE_END]);
		execve("/bin/ls", argv, env);
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
			execve("/bin/cat", &(argv[1]), env);
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
	free(test);
	return 0;
}
