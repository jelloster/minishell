/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motuomin <motuomin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:46:38 by motuomin          #+#    #+#             */
/*   Updated: 2025/01/07 21:42:13 by motuomin         ###   ########.fr       */
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
		if (!ft_strncmp(split[i], "|", 2))
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
	cmd->inredirs = NULL;
	cmd->outredir = NONE;
	cmd->args = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->infiles = NULL;
	cmd->outfiles = NULL;
	cmd->pathed_cmd = NULL;
	cmd->outfile_n = 0;
	cmd->infile_n = 0;
	cmd->pn = ms->program_name;
	ms->parsed_cmds++;
}

int	c_a_f_p(t_cmd *cmd, char **split, size_t size, t_ms *ms)
{
	int	i;

	i = -1;
	while (++i < (int)size)
	{
		cmd->args[i] = ft_strdup(split[i]);
		if (!cmd->args[i])
			return (0);
	}
	if (!expand_args(cmd, ms))
		return (0);
	return (1);
}

t_cmd	*syntax_error(char **split, t_ms *ms)
{
	free_array_of_arrays(split);
	write(2, ms->program_name + 2, ft_strlen(ms->program_name) - 2);
	write(2, ": syntax error\n", 16);
	return (NULL);
}
