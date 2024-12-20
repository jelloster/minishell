/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motuomin <motuomin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:07:00 by motuomin          #+#    #+#             */
/*   Updated: 2024/12/09 18:14:21 by motuomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	free_memory(t_cmd *cmds, t_aae *aae)
{
	int	i;

	i = 0;
	if (cmds)
	{
		while (i < aae->ac - 3)
		{
			if (cmds[i].pathed_cmd && cmds[i].args[0] != cmds[i].pathed_cmd)
				ft_memdel(&cmds[i].pathed_cmd);
			if (cmds[i].args)
				free_array_of_arrays(cmds[i].args);
			i++;
		}
		free(cmds);
		cmds = NULL;
	}
	if (aae)
	{
		if (aae->paths)
			free_array_of_arrays(aae->paths);
		free (aae);
		aae = NULL;
	}
	return (1);
}

void	fork_error(t_cmd *cmds, t_aae *aae)
{
	free_memory(cmds, aae);
	perror("Fork error.");
	exit(EXIT_FAILURE);
}

void	pipe_error(t_cmd *cmds, t_aae *aae)
{
	free_memory(cmds, aae);
	perror("Pipe error.");
	exit(EXIT_FAILURE);
}

void	memory_error(t_cmd *cmds, t_aae *aae)
{
	free_memory(cmds, aae);
	exit(EXIT_FAILURE);
}
