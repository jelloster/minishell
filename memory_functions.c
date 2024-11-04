/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motuomin <motuomin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:07:31 by motuomin          #+#    #+#             */
/*   Updated: 2024/11/04 16:29:26 by motuomin         ###   ########.fr       */
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
			if (cmds[i].pathed_cmd && cmds[i].args[0] != cmds[i].pathed_cmd) // heap buffer overflow
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
	return(0);
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
