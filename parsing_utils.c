#include "minishell.h"

int	free_n_exit(char *t_cmd, char *s_cmd, char **args, int ret)
{
	size_t	i;

	i = 0;
	if (t_cmd)
		free(t_cmd);
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

size_t	count_cmds(char **split)
{
	size_t	pipe_count;
	size_t	i;

	pipe_count = 0;
	i = 0;
	while (split[i])
	{
		if (ft_strncmp(split[i], "|", ft_strlen(split[i])) == 0)
			pipe_count++;
		i++;
	}
	if (pipe_count)
		return (pipe_count + 1);
	else if (i == 0)
		return (0);
	else
		return (1);
}

void	init_cmd(t_cmd *cmd, t_ms *ms)
{
	cmd->envp = ms->envp;
	cmd->redir = NONE;
	cmd->file = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->pathed_cmd = NULL;
}
