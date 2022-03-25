#include "pipex.h"

void	ft_puterr(char *err_msg)
{
	write(STDERR_FILENO, err_msg, ft_strlen(err_msg));
	write(STDERR_FILENO, "\n", sizeof(char));
}