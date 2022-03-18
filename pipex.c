#include "pipex.h"
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

typedef struct s_command {
	char	**cmd1;
	char	**cmd2;
	char	**envp;
	bool	is_error;
}	t_command;

int			pipeline(char *argv1[], char *argv2[], char *envp[], pid_t pids[]);
void		put_error(char *err_msg);
t_command	parse_command(char *cmd1, char *cmd2, char *envp[]);

int	main(int argc, char *argv[], char *envp[])
{
	pid_t		pids[2];
	t_command	cmd;

	if (argc < 5 || ft_strlen(argv[2]) == 0 || ft_strlen(argv[3]) == 0)
	{
		put_error("Usage: pipex file1 cmd1 cmd2 file2");
		return (EXIT_FAILURE);
	}
	cmd = parse_command(argv[2], argv[3], envp);
	pipeline(cmd.cmd1, cmd.cmd2, envp, pids);
	waitpid(pids[0], NULL, 0);
	waitpid(pids[1], NULL, 0);
	free_split(cmd.cmd1);
	free_split(cmd.cmd2);
	system("leaks pipex");
}

t_command	parse_command(char *cmd1, char *cmd2, char *envp[])
{
	t_command	command;

	command.cmd1 = ft_split(cmd1, ' ');
	if (command.cmd1 == NULL)
	{
		command.is_error = true;
		return (command);
	}
	command.cmd2 = ft_split(cmd2, ' ');
	if (command.cmd2 == NULL)
	{
		free_split(command.cmd1);
		command.is_error = true;
		return (command);
	}
	command.envp = envp;
	command.is_error = false;
	return (command);
}

void	put_error(char *err_msg)
{
	perror("pipex");
	write(2, err_msg, ft_strlen(err_msg));
	write(2, "\n", 1);
}

int	pipeline(char *argv1[], char *argv2[], char *envp[], pid_t pids[])
{
	int		fds[2];

	if (pipe(fds) == -1)
	{
		perror("pipe: An error occured with creating the pipe");
		return (EXIT_FAILURE);
	}
	pids[0] = fork();
	if (pids[0] == -1)
	{
		perror("fork: An error occured with fork");
		return (EXIT_FAILURE);
	}
	if (pids[0] == 0)
	{
		close(fds[0]);
		dup2(fds[1], STDOUT_FILENO);
		close(fds[1]);
		execve(get_executable_path(argv1[0], envp), argv1, envp);
		perror("execve: An error occured with execve");
		return (EXIT_FAILURE);
	}
	close(fds[1]);
	pids[1] = fork();
	if (pids[1] == -1)
	{
		perror("fork: An error occured with fork");
		return (EXIT_FAILURE);
	}
	if (pids[1] == 0)
	{
		dup2(fds[0], STDIN_FILENO);
		close(fds[0]);
		execve(get_executable_path(argv2[0], envp), argv2, envp);
		perror("execve: An error occured with execve");
		return (EXIT_FAILURE);
	}
	close(fds[0]);
	return (EXIT_SUCCESS);
}
