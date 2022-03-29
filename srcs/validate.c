#include "pipex.h"

bool	is_argc_valid(int argc)
{
	if (argc - 1 < 4)
	{
		ft_puterr("Invalid argument");
		ft_puterr("Usage: ./pipex infile cmd1 cmd2 [cmd3 ...] outfile");
		return (false);
	}
	else
		return (true);
}
