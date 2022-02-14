#include "includes/mini_shell.h"
#define WRITE_END 1
#define READ_END 0

int main(int argc, char const *argv[], char **env)
{
	int i = 0;

	while (argv[i])
		printf("%s\n", argv[i++]);
	return 0;
}
