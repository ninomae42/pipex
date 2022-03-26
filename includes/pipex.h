#ifndef PIPEX_H
# define PIPEX_H
# include <fcntl.h>
# include <limits.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# include <unistd.h>

// open_utils.c
int	    open_infile(const char *infile_name);
int	    open_outfile(const char *outfile_name);

// ft_syscalls.c
pid_t	ft_fork(void);
int	    ft_dup2(int filedes, int filedes2);
int	    ft_pipe(int filedes[2]);

// pipe_utils.c
void	close_pipefds(int filedes[2]);
void	pipe_setting_for_infile(char *infile_name, int pipe_fd[2]);
void	pipe_setting_for_outfile(char *outfile_name, int pipe_fd[2]);

// put_err.c
void    ft_puterr(char *err_msg);

char	*get_executable_path(char *command, char *envp[]);
void	free_split(char **search_paths);

#endif
