#include "pipex.h"

int	open_infile(const char *infile_name)
{
	int	fd;

	fd = open(infile_name, O_RDONLY | O_CLOEXEC);
	if (fd == -1)
	{
		perror("Open");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

int	open_outfile(const char *outfile_name)
{
	int	fd;

	fd = open(outfile_name, O_RDWR | O_CREAT | O_CLOEXEC,
			S_IRWXU | S_IRWXG | S_IRWXO);
	if (fd == -1)
	{
		perror("Open");
		exit(EXIT_FAILURE);
	}
	return (fd);
}