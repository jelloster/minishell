#include "minishell.h"

static int	free_n_exit(char *p_cmd, char *s_cmd, char **args, int ret);
static int	extract_pathed_cmd(t_cmd *cmd, char **paths);


/*
 * Extract command from command line into:
 *    - args (e.g., args = "ls", "-l")
 *    - pathed_cmd (e.g., "usr/bin/ls")
 *
 * Returns:
 *    1 : command extracted succesfully
 *    0 : command not found
 *   -1 : memory error
 */
int	extract_command(char *cmd_line, t_ms *ms, t_cmd *cmd)
{
	char	*no_path_cmd;

	// Check for pipes and other special characters
	// ...
	
	cmd->args = cmd_split(cmd_line); // malloc
	if (cmd->args == NULL)
		return (-1);

	// If given cmd was pathed
	if (access(cmd->args[0], X_OK) == 0)
	{
		cmd->pathed_cmd = cmd->args[0];
		no_path_cmd = cmd->args[0] + strlen_mod(cmd->args[0], '/');
		cmd->args[0] = no_path_cmd;
	}
	else
		return (extract_pathed_cmd(cmd, ms->paths));
	return (1);
}

static int	extract_pathed_cmd(t_cmd *cmd, char **paths)
{
	size_t	i;
	char	*pathed_cmd;
	char	*slashed_cmd;

	i = 0;
	if (paths == NULL)
		return (0);
	if (cmd->args[0])
		slashed_cmd = ft_strjoin("/", cmd->args[0]);
	if (!slashed_cmd)
		return (-1);
	while (paths[i] != NULL)
	{
		pathed_cmd = ft_strjoin(paths[i++], slashed_cmd);
		if (!pathed_cmd)
			return (free_n_exit(NULL, slashed_cmd, cmd->args, -1));
		if (access(pathed_cmd, X_OK) == 0)
		{
			cmd->pathed_cmd = pathed_cmd;
			return (free_n_exit(NULL, slashed_cmd, NULL, 1));
		}
		free(pathed_cmd);
	}
	return (free_n_exit(NULL, slashed_cmd, NULL, 0));
}

static int	free_n_exit(char *p_cmd, char *s_cmd, char **args, int ret)
{
	size_t	i;

	i = 0;
	if (p_cmd)
		free(p_cmd);
	if (s_cmd)
		free(s_cmd);
	if (args)
	{
		while (args[i])
			free(args[i++]);
		free(args);
	}
	return (ret);
}

/*
int	exe_cmd(t_cmd cmd)
{
	if (cmd.pathed_cmd == NULL || access(cmd.pathed_cmd, F_OK) == -1)
	{
		error_msg(COMMAND_NOT_FOUND, cmd.args[0], cmd.aae->av[0]);
		exit(127);
	}
	if (access(cmd.pathed_cmd, X_OK) == 0)
		execve(cmd.pathed_cmd, cmd.args, cmd.aae->envp);
	else
		exit(126);
	exit(2);
} */
