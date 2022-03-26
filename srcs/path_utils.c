#include "pipex.h"
#include "libft.h"

static char	**get_search_paths(char *envp[]);
static char	*get_full_path(char *command, char *environment_path);
void		free_split(char **search_paths);

char	*get_executable_path(char *command, char *envp[])
{
	char	*executable_path;
	char	**search_paths;
	char	*tmp;
	size_t	i;

	search_paths = get_search_paths(envp);
	if (search_paths == NULL)
		return (NULL);
	executable_path = NULL;
	i = 0;
	while (search_paths[i] != NULL)
	{
		tmp = get_full_path(command, search_paths[i]);
		if (tmp != NULL)
		{
			if (access(tmp, F_OK) == 0)
				executable_path = tmp;
			else
				free(tmp);
		}
		i++;
	}
	free_split(search_paths);
	return (executable_path);
}

void	free_split(char **search_paths)
{
	size_t	i;

	i = 0;
	while (search_paths[i] != NULL)
	{
		free(search_paths[i]);
		i++;
	}
	free(search_paths);
}

static char	*get_full_path(char *command, char *environment_path)
{
	char	*full_path;
	char	*tmp;

	tmp = ft_strjoin(environment_path, "/");
	if (tmp == NULL)
		return (NULL);
	full_path = ft_strjoin(tmp, command);
	free(tmp);
	return (full_path);
}

static char	**get_search_paths(char *envp[])
{
	char	*search_path_string;
	char	**search_paths;

	while (*envp != NULL)
	{
		if (ft_strnstr(*envp, "PATH", 4) != NULL)
			search_path_string = *envp;
		envp++;
	}
	search_path_string = ft_strtrim(search_path_string, "PATH=");
	if (search_path_string == NULL)
		return (NULL);
	search_paths = ft_split(search_path_string, ':');
	free(search_path_string);
	return (search_paths);
}
