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

char	**ft_split(char const *s, char c);
char	*ft_stpcpy(char *dst, const char *src);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
char	*ft_strjoin(const char *s1, const char *s2);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strrchr(const char *s, int c);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, size_t start, size_t len);

#endif
