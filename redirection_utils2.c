#include "minishell.h"

static int	count_inredirs(t_cmd *cmd)
{
	int	count;
	int	i;
	int	len;

	count = 0;
	i = 0;
	while (cmd->args[i])
	{
		len = ft_strlen(cmd->args[i]);
		if (!ft_strncmp("<", cmd->args[i], len) || !ft_strncmp("<<", cmd->args[i], len))
			count++;
		i++;
	}
	return (count);
}

static int	count_outredirs(t_cmd *cmd)
{
	int	count;
	int	i;
	int	len;

	count = 0;
	i = 0;
	while (cmd->args[i])
	{
		len = ft_strlen(cmd->args[i]);
		if (!ft_strncmp(">", cmd->args[i], len) || !ft_strncmp(">>", cmd->args[i], len))
			count++;
		i++;
	}
	return (count);
}

int	malloc_for_redirs(t_cmd *cmd)
{
	cmd->infile_n = count_inredirs(cmd);
	cmd->infiles = malloc((cmd->infile_n + 1) * sizeof(char *));
	if (!cmd->infiles)
		return (-1);
	cmd->infiles[cmd->infile_n] = NULL;

	cmd->outfile_n = count_outredirs(cmd);
	cmd->outfiles = malloc((cmd->outfile_n + 1) * sizeof(char *));
	if (!cmd->outfiles)
	{
		free_array_of_arrays(cmd->infiles);
		cmd->infiles = NULL;
		return (-1);
	}
	cmd->outfiles[cmd->outfile_n] = NULL;
	return (1);
}

/*
int	free_redirs(char **inf, char **outf)
{
	if (inf)
	{
		free_array_of_arrays(inf);
		inf = NULL;
	}
	if (inr)
	{
		free(inr);
		inr = NULL;
	} 
	if (outf)
	{
		free_array_of_arrays(outf);
		outf = NULL;
	}
	if (outr)
	{
		free(outr);
		inr = NULL;
	}
}*/
