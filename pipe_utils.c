#include "pipex.h"
#define READ 0
#define WRITE 1

void	close_pipefds(int filedes[2])
{
	close(filedes[0]);
	close(filedes[1]);
}

void	pipe_setting_for_infile(char *infile_name, int pipe_fd[2])
{
	int	infile_fd;

	infile_fd = open_infile(infile_name);
	close(pipe_fd[READ]);
	ft_dup2(infile_fd, STDIN_FILENO);
	ft_dup2(pipe_fd[WRITE], STDOUT_FILENO);
}

void	pipe_setting_for_outfile(char *outfile_name, int pipe_fd[2])
{
	int		outfile_fd;

	outfile_fd = open_outfile(outfile_name);
	close(pipe_fd[WRITE]);
	ft_dup2(pipe_fd[READ], STDIN_FILENO);
	ft_dup2(outfile_fd, STDOUT_FILENO);
}