#include "../includes/mini_shell_bonus.h"

/**
 * @brief check if the to match is a wildcard (have a '*' character)
 * 
 * @param to_match the string to check
 * @return ** _Bool true (1) if the string have a '*', false (0) else
 */
static _Bool	is_wildcards(char *to_match)
{
	size_t	i;

	i = 0;
	while (to_match[i])
		if (to_match[i++] == '*')
			return (true);
	return (false);
}

/**
 * @brief Get the all files of the current directory
 * 
 * @return char** filenames's array of the directory
 */
static char	**get_all_files(t_shell *shell, char *to_match)
{
	DIR				*dir;
	struct dirent	*file;
	char			*cpy;
	char			**ret;

	errno = 0;
	dir = opendir(".");
	if (!dir)
	{
		perror(".");
		return (NULL);
	}
	file = readdir(dir);
	while (file)
	{
		cpy = ft_track(ft_strdup(file->d_name), shell->t_pars);
		if (!cpy)
		{
			// !!!!!!!!!!!!!!!!!
		}
		file = readdir(dir);
	}
}

/**
 * @brief get a filepath and return all the paths which are corresponding
 * 
 * @param shell the minishell
 * @param to_match the filepath
 * @return char* 
 */
char	*wildcards_file(t_shell *shell, char *to_match)
{
	char	*ret;

	ret = NULL;
	if (!is_wildcards(to_match))
		return (to_match);
	
}