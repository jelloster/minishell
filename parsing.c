#include "minishell.h"

static size_t	count_cmds(char **split);
static int	handle_cmd_block(t_cmd *cmd, char **split, size_t size, t_ms *ms);
static int	extract_pathed_cmd(t_cmd *cmd, char **paths);
static int	init_cmds(t_cmd *cmds, char **split, t_ms *ms);
static int	free_n_exit(char *p_cmd, char *s_cmd, char **args, int ret);

int	parse(char *cmd_line, t_ms *ms)
{
	char	**split;
	t_cmd	*cmds;


	split = cmd_split(cmd_line);
	if (!split)
		return (-1);
	cmds = malloc (count_cmds(split) * sizeof(t_cmd)); // malloc
	/*
	for(int i = 0; split_cmd_line[i]; i++)
	{
		printf("%s\n", split_cmd_line[i]);
	}
	printf("There are %ld commands.\n", count_cmds(split_cmd_line));
	*/
	init_cmds(cmds, split, ms);
	
	
	return (1);
}

static int	init_cmds(t_cmd *cmds, char **split, t_ms *ms)
{
	size_t	i;
	size_t	j;
	size_t	cmd_i;

	i = 0; // end of command block
	j = 0; // beginning of command block
	cmd_i = 0;
	while (split[i])
	{
		if (ft_strncmp(split[i], "|", ft_strlen(split[i])) == 0)
		{
			i++;
			handle_cmd_block(&cmds[cmd_i++], &split[j], i - j - 1, ms);
			j = i;
		}
		/*
		else if (ft_strncmp(split[i], ">", ft_strlen(split[i])) == 0)
			return (0);
		else if (ft_strncmp(split[i], "<", ft_strlen(split[i])) == 0)
			return (0);
		else if (ft_strncmp(split[i], ">>", ft_strlen(split[i])) == 0)
			return (0);
		else if (ft_strncmp(split[i], "<<", ft_strlen(split[i])) == 0)
			return (0); */
		else
			i++;
	}
	return (1);
}

static int	handle_cmd_block(t_cmd *cmd, char **split, size_t size, t_ms *ms)
{
	size_t	i;
	char	*no_path_cmd;

	i = 0;
	cmd->args = malloc((size) * sizeof(char *)); // malloc
	if (!cmd->args)
		return (-1);
	while (i < size)
	{
		cmd->args[i] = split[i];
		i++;
	}
	if (access(cmd->args[0], X_OK) == 0)
	{
		cmd->pathed_cmd = cmd->args[0];
		no_path_cmd = cmd->args[0] + strlen_mod(cmd->args[0], '/');
		cmd->args[0] = no_path_cmd;
	}
	else
		return (extract_pathed_cmd(cmd, ms->paths)); // diff if there is >
	// e.g., infile > grep "hello"

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

static size_t	count_cmds(char **split)
{
	size_t	count;
	size_t	pipe_count;
	size_t	i;

	count = 0;
	pipe_count = 0;
	i = 0;
	while (split[i])
	{
		if (ft_strncmp(split[i], "|", ft_strlen(split[i])) == 0)
			pipe_count++;
		i++;
	}
	if (pipe_count)
		count = pipe_count + 1;
	else
		count = 1;
	return (count);
}
