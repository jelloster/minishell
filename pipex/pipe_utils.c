/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motuomin <motuomin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:47:35 by motuomin          #+#    #+#             */
/*   Updated: 2024/11/04 12:38:27 by motuomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	write_to_pipe(t_cmd cmd, int *fd, t_ms *ms)
{
	if (cmd.inredir == INPUT && cmd.infile)
	{
		if (access(cmd.infile, R_OK) != 0)
		{
			if (errno == ENOENT)
				error_msg(FILE_NOT_FOUND, cmd.infile, cmd.program_name);
			else if (errno == EACCES)
				error_msg(PERMISSION_DENIED, cmd.infile, cmd.program_name);
			return (0);
		}
	}
	/* else if(cmd.inredir = STDIN)
	 */

	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	return (exe_cmd(&cmd, ms));
}

int	read_and_write(t_cmd cmd, int fd_r, int fd_w, t_ms *ms)
{
	dup2(fd_r, STDIN_FILENO);
	dup2(fd_w, STDOUT_FILENO);
	close(fd_r);
	close(fd_w);
	return (exe_cmd(&cmd, ms));
}

int	read_from_pipe(t_cmd cmd, int fd, t_ms *ms)
{
	dup2(fd, STDIN_FILENO);
	if (cmd.outfile)
		redirect_output(cmd.outfile, &cmd);
	close(fd);
	return (exe_cmd(&cmd, ms));
}

int	redirect_input(char *file, t_cmd *cmd)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		if (access(file, R_OK) != 0)
		{
			if (errno == ENOENT)
				error_msg(FILE_NOT_FOUND, file, cmd->program_name);
			else if (errno == EACCES)
				error_msg(PERMISSION_DENIED, file, cmd->program_name);
		}
		return (0);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (1);
}

int	redirect_output(char *file, t_cmd *cmd)
{
	int	fd;

	if (cmd->outredir == REPLACE)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	else if (cmd->outredir == ADD)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (fd == -1)
	{
		error_msg(PERMISSION_DENIED, file, cmd->program_name);
		return (0);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (1);
}
