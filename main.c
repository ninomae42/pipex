#include "pipex.h"

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
	pids[1] = ft_fork();
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
	system("leaks pipex");
	return (EXIT_SUCCESS);
}
