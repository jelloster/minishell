/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motuomin <motuomin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:46:38 by motuomin          #+#    #+#             */
/*   Updated: 2024/11/04 16:06:40 by motuomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Function: exe_cmd
 *
 * Executes a command (cmd) using execve.
*/

int	exe_cmd(t_cmd *cmd)
{
	if (cmd->inredir == INPUT && cmd->infile)
		redirect_input(cmd->infile);
	if (cmd->outredir == REPLACE && cmd->outfile)
		redirect_output(cmd->outfile);
	if (access(cmd->pathed_cmd, X_OK) == 0) // needed?
	{
		execve(cmd->pathed_cmd, cmd->args, cmd->envp);
		return (2);
	}
	// reset out and in?
	return (0);
}
