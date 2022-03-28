/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@stdent.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 22:50:06 by tashimiz          #+#    #+#             */
/*   Updated: 2022/03/28 22:05:03 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#define READ 0
#define WRITE 1

void	close_pipefds(int filedes[2])
{
	close(filedes[0]);
	close(filedes[1]);
}

void	pipe_setting_for_infile(int infile_fd, int pipe_fd[2])
{
	close(pipe_fd[READ]);
	ft_dup2(infile_fd, STDIN_FILENO);
	ft_dup2(pipe_fd[WRITE], STDOUT_FILENO);
}

void	pipe_setting_for_outfile(int outfile_fd, int pipe_fd[2])
{
	close(pipe_fd[WRITE]);
	ft_dup2(pipe_fd[READ], STDIN_FILENO);
	ft_dup2(outfile_fd, STDOUT_FILENO);
}
