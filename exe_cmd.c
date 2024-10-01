#include "minishell.h"

/*
	Executes a command with a fork.
*/
void	exe_cmd(t_cmd cmd, char *envp[])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
	{
		if (access(cmd.pathed_cmd, X_OK) == 0)
			execve(cmd.pathed_cmd, cmd.args, envp);
	}
}
