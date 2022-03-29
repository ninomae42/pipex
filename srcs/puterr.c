#include "pipex.h"
#include "libft.h"

void	ft_puterr(char *s)
{
	ft_putendl_fd(s, STDERR_FILENO);
}
