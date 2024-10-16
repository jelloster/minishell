#include "minishell.h"

/*
	Executes a command with a fork.
*/

int	exe_cmd(t_cmd *cmd)
{
	//pid_t	pid;

	//pid = fork(); // this fork fucks with waitpid probably
	//printf("Process forked. Pid: %d.\n", pid);
	//if (pid == -1)
		//exit(1);
	//if (pid == 0)
	//{
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
		// reset output / input ? 

	//}
	//printf("pid %d exit exe cmd\n", pid);
	return (0);
}
