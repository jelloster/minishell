/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motuomin <motuomin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:47:35 by motuomin          #+#    #+#             */
/*   Updated: 2024/06/18 16:15:12 by motuomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	redirect_input(char *file);
static void	redirect_output(char *file, t_aae aae);

int	write_to_pipe(char *infile, t_cmd cmd, int *fd)
{
	if (access(infile, R_OK) != 0)
	{
		if (errno == ENOENT)
			error_msg(FILE_NOT_FOUND, infile, cmd.aae->av[0]);
		else if (errno == EACCES)
			error_msg(PERMISSION_DENIED, infile, cmd.aae->av[0]);
		exit (0);
	}
	redirect_input(infile);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	return (exe_cmd(cmd));
}

int	read_and_write(t_cmd cmd, int fd_r, int fd_w)
{
	dup2(fd_r, STDIN_FILENO);
	dup2(fd_w, STDOUT_FILENO);
	close(fd_r);
	close(fd_w);
	return (exe_cmd(cmd));
}

int	read_from_pipe(char *outfile, t_cmd cmd, int fd)
{
	dup2(fd, STDIN_FILENO);
	redirect_output(outfile, *cmd.aae);
	close(fd);
	return (exe_cmd(cmd));
}

static void	redirect_input(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		exit(0);
	dup2(fd, STDIN_FILENO);
	close(fd);
}

static void	redirect_output(char *file, t_aae aae)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd == -1)
	{
		error_msg(PERMISSION_DENIED, file, aae.av[0]);
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}
