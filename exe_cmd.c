#include "minishell.h"

/*
	Executes a command with a fork.
*/

int	exe_cmd(t_cmd *cmd)
{
	if (cmd->redir != NONE)
	{
		if (cmd->redir == INPUT)
			redirect_input(cmd->file);
		else if (cmd->redir == REPLACE)
			redirect_output(cmd->file);
	}
	if (access(cmd->pathed_cmd, X_OK) == 0) // needed?
	{
		execve(cmd->pathed_cmd, cmd->args, cmd->envp);
		return (2);
	}
	// reset out and in?
	return (0);
}
