/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motuomin <motuomin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:47:35 by motuomin          #+#    #+#             */
/*   Updated: 2025/01/13 17:05:22 by motuomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	redirect_input(char *file, t_cmd *cmd)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		if (access(file, R_OK) != 0)
		{
			if (errno == ENOENT)
				error_msg(FILE_NOT_FOUND, file, cmd->pn);
			else if (errno == EACCES)
				error_msg(PERMISSION_DENIED, file, cmd->pn);
		}
		return (0);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (1);
}

int	redirect_output(char *file, t_cmd *cmd)
{
	int			fd;
	struct stat	statbuf;

	if (cmd->outredir == REPLACE)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (fd == -1)
	{
		if (stat(file, &statbuf) == 0 && S_ISDIR(statbuf.st_mode))
			error_msg(IS_DIRECTORY, file, cmd->pn);
		else
			error_msg(PERMISSION_DENIED, file, cmd->pn);
		return (0);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (1);
}

int	wait_and_close(pid_t *pids, int cmd_n)
{
	int	exit_status;
	int	last_status;
	int	i;

	i = 0;
	last_status = 0;
	while (i < cmd_n)
	{
		waitpid(pids[i], &exit_status, 0);
		if (WIFEXITED(exit_status))
			last_status = WEXITSTATUS(exit_status);
		i++;
	}
	free(pids);
	return (last_status);
}
