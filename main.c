#include "pipex.h"

//void	validate_argument(int argc, char *argv[]);
void	validate_argument(int argc)
{
	if (argc - 1 < 4)
	{
		ft_puterr("Too few aruguments");
		ft_puterr("Usage: ./pipex infile cmd1 cmd2 [cmd3 ...] outfile");
		exit(EXIT_FAILURE);
	}
}

void	exec_command(char *cmd, char **environ)
{
	char	*exec_file_location;
	char	**cmd_vec;

	cmd_vec = ft_split(cmd, ' ');
	if (cmd_vec == NULL)
		exit(1);
	exec_file_location = get_executable_path(cmd_vec[0], environ);
	if (exec_file_location != NULL)
	{
		if (execve(exec_file_location, cmd_vec, environ) == -1)
		{
			perror("exec");
			exit(EXIT_FAILURE);
		}
	}
}

void	execute_command(int argc, char *argv[], char **environ)
{
	int		pipe_fd[2];
	pid_t	pids[2];

	ft_pipe(pipe_fd);
	pids[0] = ft_fork();
	if (pids[0] == 0)
	{
		pipe_setting_for_infile(argv[1], pipe_fd);
		exec_command(argv[2], environ);
	}
	waitpid(pids[0], NULL, 0);
	pids[1]= ft_fork();
	if (pids[1] == 0)
	{
		pipe_setting_for_outfile(argv[argc - 1], pipe_fd);
		exec_command(argv[3], environ);
	}
	close_pipefds(pipe_fd);
	waitpid(pids[1], NULL, 0);
}

int	main(int argc, char *argv[])
{
	extern char	**environ;

	validate_argument(argc);
	execute_command(argc, argv, environ);
	return (EXIT_SUCCESS);
}

// void	exec_command(char *cmd, char **environ)
// {
// 	// char	*env_path;
// 	// char	**env_path_vector;
// 	char	*exec_file_location;
// 	char	**cmd_vec;

// 	// env_path = get_env_path(environ);
// 	// if (env_path != NULL)
// 	// 	env_path_vector = ft_split(env_path, ':');
// 	// if (env_path_vector == NULL)
// 	// 	exit(1);
// 	cmd_vec = ft_split(cmd, ' ');
// 	if (cmd_vec == NULL)
// 		exit(1);
// 	// exec_file_location = get_exec_file_location(cmd_vec[0], env_path_vector);
// 	exec_file_location = get_executable_path(cmd_vec[0], environ);
// 	if (exec_file_location != NULL)
// 	{
// 		if (execve(exec_file_location, cmd_vec, environ) == -1)
// 		{
// 			perror("exec");
// 			exit(EXIT_FAILURE);
// 		}
// 	}
// }

// char	*get_env_path(char **environ)
// {
// 	char	*env_path;

// 	env_path = NULL;
// 	while (*environ != NULL)
// 	{
// 		if (ft_strnstr(*environ, "PATH=", ft_strlen("PATH=")) != NULL)
// 		{
// 			env_path = *environ;
// 			break ;
// 		}
// 		environ++;
// 	}
// 	if (env_path != NULL)
// 		env_path = ft_strtrim(env_path, "PATH=");
// 	return (env_path);
// }

// char	*create_full_path(char *env_path, char *cmd)
// {
// 	char	*environ_path;
// 	char	*full_path;

// 	environ_path = ft_strjoin(env_path, "/");
// 	full_path = ft_strjoin(environ_path, cmd);
// 	free(environ_path);
// 	return (full_path);
// }

// char	*get_exec_file_location(char *cmd, char **env_path_vector)
// {
// 	char	*cmd_full_path;
// 	char	*exec_file_location;

// 	exec_file_location = NULL;
// 	while (*env_path_vector != NULL)
// 	{
// 		cmd_full_path = create_full_path(*env_path_vector, cmd);
// 		if (cmd_full_path != NULL && access(cmd_full_path, F_OK) == 0)
// 			exec_file_location = cmd_full_path;
// 		else if (cmd_full_path != NULL)
// 			free(cmd_full_path);
// 		free(*env_path_vector);
// 		env_path_vector++;
// 	}
// 	// free(env_path_vector);
// 	return (exec_file_location);
// }


// void	exec(int argc, char *argv[], char **environ)
// {
// 	int		pipe_fd[2];
// 	int		infile_fd;
// 	int		outfile_fd;
// 	pid_t	pid1;
// 	pid_t	pid2;

// 	ft_pipe(pipe_fd);
// 	pid1 = ft_fork();
// 	if (pid1 == 0) {
// 		close(pipe_fd[READ]);
// 		infile_fd = open_infile(argv[1]);
// 		ft_dup2(pipe_fd[WRITE], STDOUT_FILENO);
// 		ft_dup2(infile_fd, STDIN_FILENO);
// 		close(infile_fd);
// 		execle("/bin/ls", "ls", "-l", NULL, environ);
// 		exit(EXIT_FAILURE);
// 	}
// 	pid2 = ft_fork();
// 	if (pid2 == 0)
// 	{
// 		close(pipe_fd[WRITE]);
// 		outfile_fd = open_outfile(argv[argc - 1]);
// 		ft_dup2(pipe_fd[READ], STDIN_FILENO);
// 		ft_dup2(outfile_fd, STDOUT_FILENO);
// 		close(outfile_fd);
// 		execle("/usr/bin/grep", "grep", "ft", NULL, environ);
// 		exit(EXIT_FAILURE);
// 	}
// 	close(pipe_fd[READ]);
// 	close(pipe_fd[WRITE]);
// 	waitpid(pid2, NULL, 0);
// }