/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motuomin <motuomin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:07:00 by motuomin          #+#    #+#             */
/*   Updated: 2024/06/18 16:11:18 by motuomin         ###   ########.fr       */
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

void	error_msg(int error, char *str, char *binary)
{
	char	*b;

	if (ft_strchr(binary, '/'))
		b = binary + ((ft_strrchr(binary, '/') + 1) - binary);
	else
		b = binary;
	ft_putstr_fd(b, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (str && error != PERMISSION_DENIED)
		ft_putstr_fd(str, STDERR_FILENO);
	if (error == FILE_NOT_FOUND)
		ft_putstr_fd(": No such file or directory", STDERR_FILENO);
	else if (error == COMMAND_NOT_FOUND)
		ft_putstr_fd(": command not found", STDERR_FILENO);
	else if (error == PERMISSION_DENIED)
	{
		ft_putstr_fd("permission denied: ", STDERR_FILENO);
		if (str)
			ft_putstr_fd(str, STDERR_FILENO);
	}
	ft_putstr_fd("\n", STDERR_FILENO);
}
