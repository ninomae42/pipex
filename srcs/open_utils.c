/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@stdent.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 22:49:58 by tashimiz          #+#    #+#             */
/*   Updated: 2022/03/28 21:58:32 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	open_iofiles(int io_files[], int argc, char *argv[])
{
	bool	is_err;

	is_err = false;
	if (access(argv[1], F_OK) != 0)
	{
		ft_perror("pipex", ENOENT);
		ft_puterr(argv[1]);
		is_err = true;
	}
	else
		io_files[0] = open_infile(argv[1]);
	if (access(argv[argc - 1], F_OK) == 0)
	{
		ft_perror("pipex", EEXIST);
		ft_puterr(argv[argc - 1]);
		is_err = true;
	}
	else
		io_files[1] = open_outfile(argv[argc - 1]);
	if (is_err)
	{
		close_pipefds(io_files);
		exit(EXIT_FAILURE);
	}
}

int	open_infile(const char *infile_name)
{
	int	fd;

	fd = open(infile_name, O_RDONLY | O_CLOEXEC);
	if (fd == -1)
	{
		ft_perror("pipex", errno);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

int	open_outfile(const char *outfile_name)
{
	int	fd;

	fd = open(outfile_name, O_RDWR | O_CREAT | O_CLOEXEC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	if (fd == -1)
	{
		ft_perror("pipex", errno);
		exit(EXIT_FAILURE);
	}
	return (fd);
}
