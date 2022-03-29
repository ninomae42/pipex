#include "pipex.h"

int	main(int argc, char *argv[])
{
	extern char	**environ;
	int			status;

	if (!is_argc_valid(argc))
		exit(EXIT_FAILURE);
	status = pipe_and_exec(argc, argv, environ);
	return (status);
}
