#include "minishell.h"

static void	redirect_input(char *file);
static void	redirect_output(char *file, t_aae aae);

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
		if (cmd->redir != NONE)
		{
			if (cmd->redir == INPUT)
				redirect_input(cmd->file);
			// redirect output / input
		}
		if (access(cmd.pathed_cmd, X_OK) == 0) // needed?
			execve(cmd.pathed_cmd, cmd.args, envp);
		// reset output / input

	}
}


static void	redirect_input(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		exit(0); // ?
	dup2(fd, STDIN_FILENO);
	close(fd);
}

static void	redirect_output(char *file, t_aae aae)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd == -1)
	{
		error_msg(PERMISSION_DENIED, file, aae.av[0]);
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}
