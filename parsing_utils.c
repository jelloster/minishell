/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motuomin <motuomin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:46:38 by motuomin          #+#    #+#             */
/*   Updated: 2024/12/16 14:08:03 by motuomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Function : count_cmds
 *
 * Counts how many commands are in the (split) command line.
 *
 * Example:
 * "echo" "hello" "|" "wc" "-l"
 * count : 2
*/

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

/*
 * Function : init_cmd
 *
 * Gives the cmd struct basic info and sets pointers to null
*/

void	init_cmd(t_cmd *cmd, t_ms *ms)
{
	cmd->envp = ms->envp;
	cmd->inredir = NONE;
	cmd->outredir = NONE;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->pathed_cmd = NULL;
	cmd->outfile_n = 0;
	cmd->infile_n = 0;
	cmd->program_name = ms->program_name;
	ms->parsed_cmds++;
}

int	copy_args_from_split(t_cmd *cmd, char **split, size_t size)
{
	int	i;

	i = -1;
	while (++i < (int)size)
	{
		cmd->args[i] = ft_strdup(split[i]); // leaks
		if (!cmd->args[i])
			return (0);
	}
	return (1);
}
