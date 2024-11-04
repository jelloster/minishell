#include "minishell.h"

/*
	Executes a command with a fork.
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
