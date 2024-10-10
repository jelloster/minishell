#include "minishell.h"

static int	cmd_block(t_cmd *cmd, char **split, size_t size, t_ms *ms);
static int	init_cmds(t_cmd *cmds, char **split, t_ms *ms);

/*
 * Function: parse
 *
 * Description: Takes user input from command line and sorts it into an array
 * of executable commands (t_cmd *cmds).
 *
 * Return values:
 * - A filled out array of cmds 
 * - NULL (something went wrong)
*/

t_cmd	*parse(char *cmd_line, t_ms *ms)
{
	t_cmd	*cmds;
	char	**split_cmd_line;

	// Split the command line into separate strings
	split_cmd_line = cmd_split(cmd_line);
	if (!split_cmd_line)
		return (NULL);

	// Allocate memory for x num of commands
	mc->cmd_n = count_cmds(split_cmd_line);
	cmds = malloc (mc->cmd_n * sizeof(t_cmd)); // malloc
	if (!cmds)
	{
		free_array_of_arrays(split_cmd_line);
		return (NULL);
	}
	init_cmds(cmds, split, ms);
	return (cmds);
}

/*
 * Function: init_cmds
 *
 * Description: Takes a split command line and distributes the info to the
 * cmds in the array of commands.
 *
 * Return values:
 * 1: Everything worked
 * 0: Something went wrong
*/

static int	init_cmds(t_cmd *cmds, char **split, t_ms *ms)
{
	size_t	i;
	size_t	j;
	size_t	cmd_i;

	i = 0;
	j = 0;
	cmd_i = 0;
	while (split[i])
	{
		if (ft_strncmp(split[i], "|", ft_strlen(split[i])) == 0)
		{
			i++;
			if(!cmd_block(&cmds[cmd_i++], &split[j], i - j - 1, ms))
				return (0);
			j = i;
		}
		else
			i++;
	}
	return (1);
}

/*
 * Function: cmd_block
 *
 * Description: 
*/

static int	cmd_block(t_cmd *cmd, char **split, size_t size, t_ms *ms)
{
	char	*no_path_cmd;
	int	i;

	// Allocate memory for the command's args
	cmd->args = malloc((size) * sizeof(char *)); // malloc
	if (!cmd->args)
		return (0);

	// Assign the appropriate pointers to args
	i = -1;
	while (i++ < (int)size)
		cmd->args[i] = split[i];

	
	// Check for redirections
	if (check_fork_redirections(cmd)
		return(handle_redirected_cmd(cmd, ms->paths));
	// If not, check if the command was pathed
	else if (access(cmd->args[0], X_OK) == 0)
	{
		cmd->pathed_cmd = cmd->args[0];
		no_path_cmd = cmd->args[0] + strlen_mod(cmd->args[0], '/');
		cmd->args[0] = no_path_cmd;
	}
	// Or if we need to find the path for the command
	else
		return (extract_pathed_cmd(cmd, ms->paths));

	return (1);
}

int	extract_pathed_cmd(t_cmd *cmd, char **paths)
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
