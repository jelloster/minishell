/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motuomin <motuomin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:46:38 by motuomin          #+#    #+#             */
/*   Updated: 2024/12/16 14:59:58 by motuomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Function: exe_cmd
 *
 * Executes a command (cmd) using execve.
*/

void	create_output_files(t_cmd *cmd);
void	complain_about_input_files(t_cmd *cmd);

int	exe_cmd(t_cmd *cmd, t_ms *ms)
{
	create_output_files(cmd);
	complain_about_input_files(cmd);
	if (is_built_in(cmd->args[0]))
		return (69);
	if (cmd->inredir == INPUT && cmd->infile)
		if (!redirect_input(cmd->infile, cmd))
			return (0);
	if (cmd->inredir == STD_IN && cmd->infile)
	{
		if (!redirect_input(cmd->infile, cmd))
			return (0);
		ms->ret_val = heredoc_print(cmd);
		unlink(cmd->infile);
		exit(ms->ret_val);
	}
	if (cmd->outfile)
		if (!redirect_output(cmd->outfile, cmd))
			return (0);
<<<<<<< HEAD
	if (access(cmd->pathed_cmd, X_OK) == 0) // needed?
=======
	if (access(cmd->pathed_cmd, X_OK) == 0)
>>>>>>> 3dfb0672f06847c6fdf4e25379265633025a3a48
	{
		execve(cmd->pathed_cmd, cmd->args, ms->envp);
		return (2);
	}
	else
	{
		error_msg(COMMAND_NOT_FOUND, cmd->args[0], ms->program_name);
		exit(127);
	}
	exit (0);
}

void	complain_about_input_files(t_cmd *cmd)
{
	int		fd;
	struct stat	statbuf;
	int		i;

	i = 0;
	if (cmd->infile_n <= 1)
		return ;
	while (i < cmd->infile_n - 1)
	{
		fd = open(cmd->infiles[i], O_RDONLY); if (fd == -1)
		{
			if (access(cmd->infiles[i], R_OK) != 0)
			{
				if (errno == ENOENT)
					error_msg(FILE_NOT_FOUND, cmd->infiles[i], cmd->program_name);
				else if (stat(cmd->infiles[i], &statbuf) == 0 && S_ISDIR(statbuf.st_mode))
					error_msg(IS_DIRECTORY, cmd->infiles[i], cmd->program_name); // doesn't work
				else if (errno == EACCES)
					error_msg(PERMISSION_DENIED, cmd->infiles[i], cmd->program_name);
			}
		}
		close(fd);
		i++;
	}

}

void	create_output_files(t_cmd *cmd)
{
	int		fd;
	struct stat	statbuf;
	int		i;

	i = 0;
	if (cmd->outfile_n <= 1)
		return ;
	while (i < cmd->outfile_n - 1)
	{
		fd = open(cmd->outfiles[i], O_WRONLY | O_CREAT | O_APPEND, 0664);
		if (fd == -1)
		{
			if (stat(cmd->outfiles[i], &statbuf) == 0 && S_ISDIR(statbuf.st_mode))
				error_msg(IS_DIRECTORY, cmd->outfiles[i], cmd->program_name);
			else
				error_msg(PERMISSION_DENIED, cmd->outfiles[i], cmd->program_name);
		}
		else
			close (fd);
		i++;
	}
}
