#include "pipex.h"
#include "libft.h"

static char	*get_env_path_row(char **environ);
static char	*get_env_path(char **environ);
static char	*convert_to_full_path(char *env_path, char *command);

char	*get_exec_path_envp(char *command, char **environ)
{
	char	*exec_path;
	char	*env_path;
	char	**env_path_vec;
	size_t	i;

	env_path = get_env_path(environ);
	if (env_path == NULL)
		return (NULL);
	env_path_vec = ft_split(env_path, ':');
	i = 0;
	while (env_path_vec[i])
	{
		exec_path = convert_to_full_path(env_path_vec[i], command);
		if (access(exec_path, F_OK) == 0)
			break ;
		else
			free(exec_path);
		i++;
	}
	free_split(env_path_vec);
	return (exec_path);
}

void	free_split(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

static char	*convert_to_full_path(char *env_path, char *command)
{
	char	*full_path;
	char	*tmp;

	tmp = ft_strjoin(env_path, "/");
	full_path = ft_strjoin(tmp, command);
	free(tmp);
	return (full_path);
}

static char	*get_env_path(char **environ)
{
	char	*env_path;

	env_path = get_env_path_row(environ);
	if (env_path == NULL)
		return (NULL);
	env_path = ft_strtrim(env_path, "PATH=");
	return (env_path);
}

static char	*get_env_path_row(char **environ)
{
	char	*env_path;

	env_path = NULL;
	while (*environ)
	{
		if (ft_strncmp(*environ, "PATH=", 5) == 0)
			env_path = *environ;
		environ++;
	}
	return (env_path);
}
