#include "pipex.h"

int	open_infile(char *infile_name)
{
	int	fd;

	fd = open(infile_name, O_RDONLY | O_CLOEXEC);
	if (fd == -1)
	{
		perror("open infile");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

int	open_outfile(char *outfile_name)
{
	int	fd;

	fd = open(outfile_name, O_RDWR | O_CREAT | O_TRUNC | O_CLOEXEC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	if (fd == -1)
	{
		perror("open outfile");
		exit(EXIT_FAILURE);
	}
	return (fd);
}
