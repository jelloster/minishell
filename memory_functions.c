/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motuomin <motuomin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:07:31 by motuomin          #+#    #+#             */
/*   Updated: 2024/12/09 15:37:55 by motuomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_cmds(t_cmd *cmds, int cmd_n)
{
	int	i;

	i = 0;
	if (cmds)
	{
		while (i < cmd_n)
		{
				//&& cmds[i].args[0] != cmds[i].pathed_cmd + find_last(cmds[i].pathed_cmd, '/') + 1)
			if (cmds[i].pathed_cmd && cmds[i].pathed_cmd != cmds[i].args[0])
				ft_memdel(&cmds[i].pathed_cmd);
			if (cmds[i].args)
				free_array_of_arrays(cmds[i].args);
			if (cmds[i].infile)
				ft_memdel(&cmds[i].infile);
			if (cmds[i].outfile)
				ft_memdel(&cmds[i].outfile);
			i++;
		}
		free(cmds);
		cmds = NULL;
	}
	return (0);
}

int	free_ms(t_ms *ms, char *cmd_line, t_cmd *cmds, int ret)
{
	if (ms->paths)
	{
		free_array_of_arrays(ms->paths);
		ms->paths = NULL;
	}
	if (cmds)
	{
		free_cmds(cmds, ms->parsed_cmds);
	}
	if (cmd_line)
		ft_memdel(&cmd_line);
	return (ret);
}

void	*free_array_of_arrays(char **arr)
{
	size_t	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
		{
			if (arr[i])
			{
				free(arr[i]);
				arr[i] = NULL;
			}
			i++;
		}
		free(arr);
		arr = NULL;
	}
	return (NULL);
}

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

void	*cmd_free_memory(char **res, char **res_start)
{
	while (res > res_start)
		free(*(--res));
	free(res_start);
	return (NULL);
}
