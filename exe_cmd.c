/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motuomin <motuomin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:46:38 by motuomin          #+#    #+#             */
/*   Updated: 2025/01/08 22:35:24 by jkarhu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	complain_about_input_files(t_cmd *cmd)
{
	int			fd;
	int			i;

	i = -1;
	if (cmd->infile_n <= 1)
		return ;
	fd = -1;
	while (++i < cmd->infile_n - 1)
	{
		if (cmd->infiles[i] && cmd->inredirs[i] != STD_IN)
			fd = open(cmd->infiles[i], O_RDONLY);
		if (fd == -1 && cmd->infiles[i] && cmd->inredirs[i] != STD_IN)
		{
			if (access(cmd->infiles[i], R_OK) != 0)
			{
				if (errno == ENOENT)
					error_msg(FNF, cmd->infiles[i], cmd->pn);
				else if (errno == EACCES)
					error_msg(PD, cmd->infiles[i], cmd->pn);
			}
		}
		if (cmd->infiles[i] && fd != -1)
			close(fd);
	}
}

static void	create_output_files(t_cmd *cmd)
{
	int			fd;
	struct stat	statbuf;
	int			i;

	i = 0;
	if (cmd->outfile_n <= 1)
		return ;
	while (i < cmd->outfile_n - 1)
	{
		fd = open(cmd->outfiles[i], O_WRONLY | O_CREAT | O_APPEND, 0664);
		if (fd == -1)
		{
			if (stat(cmd->outfiles[i], &statbuf) == 0
				&& S_ISDIR(statbuf.st_mode))
				error_msg(ID, cmd->outfiles[i], cmd->pn);
			else
				error_msg(PD, cmd->outfiles[i], cmd->pn);
		}
		else
			close (fd);
		i++;
	}
}

int	exe_cmd(t_cmd *cmd, t_ms *ms)
{
	create_output_files(cmd);
	complain_about_input_files(cmd);
	if (is_built_in(cmd->args[0]))
		return (69);
	if (cmd->infile && (cmd->inredir == INPUT || cmd->inredir == STD_IN))
		if (!redirect_input(cmd->infile, cmd))
			return (0);
	if (cmd->inredir == STD_IN)
	{

		if (cmd->infile && access(cmd->infile, R_OK) == 0)
			unlink(cmd->infile);
		free(cmd->infile);
		if (!cmd->args[0])
			return (ms->ret_val);
	}
	if (cmd->outfile)
		if (!redirect_output(cmd->outfile, cmd))
			return (0);
	if (cmd->pathed_cmd && access(cmd->pathed_cmd, X_OK) == 0)
	{
		dollarquestion(ms, cmd);
		return (execve(cmd->pathed_cmd, cmd->args, ms->envp), 2);
	}
	else
		return (error_msg(CNF, cmd->args[0], ms->program_name), 127);
	exit (0);
}
