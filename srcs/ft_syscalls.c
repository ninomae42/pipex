#include "pipex.h"

pid_t	ft_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	return (pid);
}

int	ft_dup2(int filedes, int filedes2)
{
	int	fd;

	fd = dup2(filedes, filedes2);
	if (fd == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

int	ft_pipe(int filedes[2])
{
	if (pipe(filedes) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	return (0);
}