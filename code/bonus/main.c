#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

#include <errno.h>
#define ERROR 1
#define FOUND 0
#define NOT_FOUND 2
int main(int c, char **argv, char **env)
{
	int i =0;
	errno = 0;
	size_t	len;
	char *name = argv[1];
	struct dirent * dp;
	//while (env[i])
	//{
		//printf("%s\n", env[i++]);
	//}
	//execve("/bin/ls", argv, env);
	/*printf("%s\n", getwd(NULL));
	printf("%d\n", chdir(".."));
	printf("%s\n", getwd(NULL));*/
	printf("%s\n", name);
	DIR *dirp = opendir(".");
           if (dirp == NULL)
		   {
			   perror(".");
                   return (ERROR);
		   }
		   len = strlen(name);
           while ((dp = readdir(dirp)) != NULL) {
                   if (dp->d_namlen == len && strcmp(dp->d_name, name) == 0) {
                           (void)closedir(dirp);
                           return (FOUND);
                   }
           }
		   perror(NULL);
           (void)closedir(dirp);
           return (NOT_FOUND);
}
