/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motuomin <motuomin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:13:56 by motuomin          #+#    #+#             */
/*   Updated: 2025/01/18 14:27:32 by jkarhu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

	ms->parsed_cmds = 0;
	ms->split = cmd_split(cmd_line);
	if (!ms->split)
	{
		write(2, ms->program_name + 2, ft_strlen(ms->program_name) - 2);
		write(2, ": syntax error\n", 15);
		return (NULL);
	}
	if (!syntax_check(ms->split))
		return (syntax_error(ms->split, ms));
	ms->cmd_n = count_cmds(ms->split);
	cmds = malloc ((ms->cmd_n) * sizeof(t_cmd));
	if (!cmds)
		return (free_array_of_arrays(ms->split));
	if (!init_cmds(cmds, ms->split, ms))
	{
		free_cmds(cmds, ms->parsed_cmds);
		return (free_array_of_arrays(ms->split));
	}
	ms->cmds = cmds;
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
	int		size;

	i = 0;
	j = 0;
	ms->cmds = cmds;
	if (!update_paths(ms))
		return (0);
	while (split[i])
	{
		if (!ft_strncmp(split[i], "|", 2)
			|| !split[i + 1])
		{
			size = i - j + (split[i + 1] == NULL);
			if (cmd_block(cmds++, &split[j], size, ms) == -1)
				return (0);
			i++;
			j = i;
		}
		else
			i++;
	}
	free_array_of_arrays(split);
	return (1);
}

static int	handle_pathed_cmd(t_cmd *cmd)
{
	char	*np;

	cmd->pathed_cmd = ft_strdup(cmd->args[0]);
	if (!cmd->pathed_cmd)
		return (free_array_of_arrays(cmd->args), 0);
	np = ft_strdup(cmd->args[0] + find_last(cmd->args[0], '/') + 1);
	if (!np)
	{
		free (cmd->pathed_cmd);
		return (free_array_of_arrays(cmd->args), 0);
	}
	free(cmd->args[0]);
	cmd->args[0] = np;
	return (1);
}

/*
 * Function: cmd_block
 *
 * Description: Takes a size long command and distributes the info to *cmd
*/

static int	cmd_block(t_cmd *cmd, char **split, size_t size, t_ms *ms)
{
	init_cmd(cmd, ms);
	cmd->args = malloc((size + 1) * sizeof(char *));
	if (!cmd->args)
		return (-1);
	cmd->args[size] = NULL;
	if (!c_a_f_p(cmd, split, size, ms))
		return (-1);
	if (check_for_redirections(cmd))
		return (handle_redirected_cmd(ms, cmd, ms->paths));
	else if (is_built_in(cmd->args[0]))
		return (cmd->pathed_cmd = cmd->args[0], 1);
	else if (access(cmd->args[0], X_OK) == 0 || ft_strlen(cmd->args[0]) == 0)
	{
		if (!handle_pathed_cmd(cmd))
			return (-1);
	}
	else
		return (extract_pathed_cmd(cmd, ms->paths));
	return (1);
}

/*
 * Function : extract_pathed_cmd
 *
 * Goes through paths until it finds one that is executable
*/

int	extract_pathed_cmd(t_cmd *cmd, char **paths)
{
	size_t	i;
	char	*pathed_cmd;
	char	*slashed_cmd;

	i = 0;
	if (paths != NULL && cmd->args[0])
		slashed_cmd = ft_strjoin("/", cmd->args[0]);
	else
		return (0);
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
	cmd->pathed_cmd = cmd->args[0];
	return (free_n_exit(NULL, slashed_cmd, NULL, 0));
}
