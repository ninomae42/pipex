#include "pipex.h"
#include "libft.h"

static void	exec_command(char *command, char **environ);

int	pipe_and_exec(int argc, char *argv[], char **environ)
{
	int		status;
	int		pipe_fd[2];
	pid_t	pids[2];

	ft_pipe(pipe_fd);
	pids[0] = ft_fork();
	if (pids[0] == 0)
	{
		pipe_setting_for_infile(pipe_fd, open_infile(argv[1]));
		exec_command(argv[2], environ);
	}
	pids[1] = ft_fork();
	if (pids[1] == 0)
	{
		pipe_setting_for_outfile(pipe_fd, open_outfile(argv[argc - 1]));
		exec_command(argv[3], environ);
	}
	close_two_fds(pipe_fd);
	waitpid(pids[0], &status, 0);
	waitpid(pids[1], &status, 0);
	return (status);
}

static void	exec_command(char *command, char **environ)
{
	char	**command_vec;
	char	*command_path;

	command_vec = ft_split(command, ' ');
	if (command_vec == NULL)
		return ;
	if (access(command_vec[0], F_OK) == 0 || ft_strchr(command_vec[0], '/'))
		command_path = command_vec[0];
	else
		command_path = get_exec_path_envp(command_vec[0], environ);
	if (command_path == NULL)
		command_path = "";
	if (execve(command_path, command_vec, environ) == -1)
	{
		free_split(command_vec);
		perror("pipex");
		exit(EXIT_FAILURE);
	}
}
