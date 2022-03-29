#include "pipex.h"

void	ft_pipe(int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
	{
		perror("pipex");
		exit(EXIT_FAILURE);
	}
}

void	ft_dup2(int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
	{
		perror("pipex");
		exit(EXIT_FAILURE);
	}
}

pid_t	ft_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("pipex");
		exit(EXIT_FAILURE);
	}
	return (pid);
}
