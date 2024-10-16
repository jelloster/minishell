#include "minishell.h"

static int	cmd_block(t_cmd *cmd, char **split, size_t size, t_ms *ms);
static int	init_cmds(t_cmd *cmds, char **split, t_ms *ms);

/*
 * Function: parse
 *
 * Description: Takes user input from command line and sorts it into an array
 * of executable commands (t_cmd *cmds).
*/

t_cmd	*parse(char *cmd_line, t_ms *ms)
{
	t_cmd	*cmds;
	char	**split_cmd_line;

	// Split the command line into separate strings
	split_cmd_line = cmd_split(cmd_line); // malloc 3
	if (!split_cmd_line)
		return (NULL);

	// Allocate memory for x num of commands
	ms->cmd_n = count_cmds(split_cmd_line);
	cmds = malloc (ms->cmd_n * sizeof(t_cmd)); // malloc
	if (!cmds)
	{
		free_array_of_arrays(split_cmd_line);
		return (NULL);
	}
	init_cmds(cmds, split_cmd_line, ms);
	return (cmds);
}

/*
 * Function: init_cmds
 *
 * Description: Takes a split command line and distributes the info to the
 * cmds in the array of commands.
*/

static int	init_cmds(t_cmd *cmds, char **split, t_ms *ms)
{
	size_t	i;
	size_t	j;
	size_t	cmd_i;
	int	size;

	i = 0;
	j = 0;
	cmd_i = 0;
	while (split[i])
	{
		if (ft_strncmp(split[i], "|", ft_strlen(split[i])) == 0
			|| split[i + 1] == NULL)
		{
			if (split[i + 1] == NULL)
				size = i - j + 1;
			else
				size = i - j;
			if(!cmd_block(&cmds[cmd_i++], &split[j], size, ms))
				return (0);
			i++;
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
 * Description: Takes a size long command and distributes the info to *cmd
*/

static int	cmd_block(t_cmd *cmd, char **split, size_t size, t_ms *ms)
{
	char	*no_path_cmd;
	int	i;

	// Allocate memory for the command's args
	cmd->args = malloc((size + 1) * sizeof(char *)); // malloc
	cmd->args[size] = NULL;
	if (!cmd->args)
		return (0);

	// Give the command basic info
	init_cmd(cmd, ms);

	// Assign the appropriate pointers to args
	i = -1;
	while (++i < (int)size)
		cmd->args[i] = split[i];

	
	// Check for redirections
	if (check_for_redirections(cmd))
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
