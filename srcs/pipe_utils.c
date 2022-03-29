#include "pipex.h"

void	close_two_fds(int fds[])
{
	close(fds[0]);
	close(fds[1]);
}

void	pipe_setting_for_infile(int pipe_fd[], int infile)
{
	ft_dup2(infile, STDIN_FILENO);
	ft_dup2(pipe_fd[1], STDOUT_FILENO);
	close(infile);
	close_two_fds(pipe_fd);
}

void	pipe_setting_for_outfile(int pipe_fd[], int outfile)
{
	ft_dup2(pipe_fd[0], STDIN_FILENO);
	ft_dup2(outfile, STDOUT_FILENO);
	close(outfile);
	close_two_fds(pipe_fd);
}
