#include "../../includes/mini_shell.h"

char	*ft_cat_path(char *dir, char *cmd)
{
	char	*bin;
	int		len;
	int		full_len;

	len = ft_strlen(dir);
	full_len = len + ft_strlen(cmd) + 2;
	bin = (char *)malloc(sizeof(char) * full_len + 1);
	if (!bin)
		return (NULL);
	ft_memcpy(bin, dir, len);
	bin[len] = '/';
	len++;
	while (len < full_len)
		bin[len++] = *cmd++;
	bin[len] = '\0';
	return (bin);
}

static char	*ft_path(char **env)
{
	char	*path;
	int		i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
		i++;
	if (!env)
		return (NULL);
	path = ft_strdup(env[i] + 5);
	return (path);
}

char	*ft_get_path(char *cmd, char **env)
{
	char	*path;
	char	*ptr;
	char	*dir;
	char	*bin;

	path = ft_path(env);
	ptr = path;
	while (path && ft_strichr(path, ':') > -1)
	{
		dir = ft_strndup(path, ft_strichr(path, ':'));
		bin = ft_cat_path(dir, cmd);
		free(dir);
		if (access(bin, F_OK) == 0)
		{
			free(ptr);
			return (bin);
		}
		free(bin);
		path += ft_strichr(path, ':') + 1;
	}
	free(ptr);
	return (cmd);
}
