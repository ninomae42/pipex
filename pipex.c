#include "pipex.h"
#include <string.h>
#include <unistd.h>

char	*get_environment_path(char *envp[]);
char	**get_path_vector(char *path);
char	*get_full_path(char *command, char *environment_path);
char	*get_executable_path(char *command, char **path_vec);
void	destruct_state(char **path_vec, char *executable_path);

int	main(int argc, char *argv[], char *envp[])
{
	char	**path_vec;
	char	*executable_path;
	char	*cmd_argv[2];
	int		status;
	pid_t	pid;

	if (argc < 5 || ft_strlen(argv[1]) == 0)
		return (EXIT_FAILURE);
	cmd_argv[0] = argv[1];
	cmd_argv[1] = NULL;
	path_vec = get_path_vector(get_environment_path(envp));
	printf("argv[1]: %s\n", argv[1]);
	executable_path = get_executable_path(argv[1], path_vec);
	printf("executable_path: %s\n\n", executable_path);
	pid = fork();
	if (pid == -1)
	{
		destruct_state(path_vec, executable_path);
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		execve(executable_path, cmd_argv, envp);
		destruct_state(path_vec, executable_path);
		exit(EXIT_SUCCESS);
	}
	else
	{
		wait(&status);
		printf("\nchild process exited with status: %d\n\n", WEXITSTATUS(status));
		destruct_state(path_vec, executable_path);
		system("leaks pipex");
		exit(EXIT_SUCCESS);
	}
}

void	destruct_state(char **path_vec, char *executable_path)
{
	size_t	i;

	i = 0;
	while (path_vec[i] != NULL)
	{
		free(path_vec[i]);
		i++;
	}
	free(path_vec);
	free(executable_path);
}

char	*get_executable_path(char *command, char **path_vec)
{
	char	*executable_path;
	char	*full_path;

	executable_path = NULL;
	while (*path_vec != NULL)
	{
		full_path = get_full_path(command, *path_vec);
		if (access(full_path, F_OK) == 0)
			executable_path = full_path;
		else
			free(full_path);
		path_vec++;
	}
	return (executable_path);
}

char	*get_full_path(char *command, char *environment_path)
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

char	**get_path_vector(char *path)
{
	char	**path_vec;
	char	*trimmed_path;

	trimmed_path = ft_strtrim(path, "PATH=");
	if (trimmed_path == NULL)
		return (NULL);
	path_vec = ft_split(trimmed_path, ':');
	free(trimmed_path);
	return (path_vec);
}

char	*get_environment_path(char *envp[])
{
	while (*envp != NULL)
	{
		if (strnstr(*envp, "PATH", 4) != NULL)
			return (*envp);
		envp++;
	}
	return (NULL);
}
