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

int	write_to_pipe(t_cmd cmd, int *fd)
{
	// If there is an input file
	if (cmd.inredir == INPUT && cmd.infile)
	{
		// If the file isn't readable
		if (access(cmd.infile, R_OK) != 0)
		{
			// File not found
			if (errno == ENOENT)
			{
				error_msg(FILE_NOT_FOUND, cmd.infile, cmd.program_name);
				//return (1);
			}
			// Permission denied
			else if (errno == EACCES)
			{
				error_msg(PERMISSION_DENIED, cmd.infile, cmd.program_name);
				//return (1);
			}
			return (0);
		}
		// Redirect input to infile ??
		redirect_input(cmd.infile, &cmd);
	}
	/* else if(cmd.inredir = STDIN)
	 */

	// Redirec output to pipe's write end
	dup2(fd[1], STDOUT_FILENO);

	// Close pipe
	close(fd[0]);
	close(fd[1]);
	
	// Execute the command
	return (exe_cmd(&cmd));
}

int	read_and_write(t_cmd cmd, int fd_r, int fd_w)
{
	dup2(fd_r, STDIN_FILENO);
	dup2(fd_w, STDOUT_FILENO);
	close(fd_r);
	close(fd_w);
	return (exe_cmd(&cmd));
}

int	read_from_pipe(t_cmd cmd, int fd)
{
	dup2(fd, STDIN_FILENO);
	if (cmd.outfile)
		redirect_output(cmd.outfile, &cmd);
	close(fd);
	return (exe_cmd(&cmd));
}

int	redirect_input(char *file, t_cmd *cmd)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		// free duplicated memory
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

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0664); // CHANGE
	if (fd == -1)
	{
		
		error_msg(PERMISSION_DENIED, file, cmd->program_name);
		// free duplicated memory
		return (0); // return?
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (1);
}
