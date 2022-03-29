#ifndef PIPEX_H
# define PIPEX_H
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

// exec.c
int		pipe_and_exec(int argc, char *argv[], char **environ);

// ft_syscall.c
void	ft_pipe(int pipe_fd[2]);
void	ft_dup2(int fd1, int fd2);
pid_t	ft_fork(void);

// get_path_envp.c
char	*get_exec_path_envp(char *command, char **environ);
void	free_split(char **array);

// open_utils.c
int		open_infile(char *infile_name);
int		open_outfile(char *outfile_name);

// pipe_utils.c
void	pipe_setting_for_infile(int pipe_fd[], int infile);
void	pipe_setting_for_outfile(int pipe_fd[], int outfile);
void	close_two_fds(int fds[]);

// puterr.c
void	ft_puterr(char *s);
bool	is_argc_valid(int argc);

// validate.c
bool	is_argc_valid(int argc);

#endif
