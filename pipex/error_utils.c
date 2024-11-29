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
	int	temp_fd;
	int	original_fd;

	temp_fd = open("/tmp/error_log.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (temp_fd == -1)
		return ;
	original_fd = dup(STDERR_FILENO);
	if (original_fd == -1)
	{
		close(temp_fd);
		return ;
	}
	if (dup2(temp_fd, STDERR_FILENO) == -1)
	{
		close(temp_fd);
		close(original_fd);
		return ;
	}
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

	if (dup2(original_fd, STDERR_FILENO) == -1)
		perror("Failed to reset stderr");
	close(temp_fd);
	close(original_fd);
}

void	print_and_clear_errorlog(void)
{
	int	fd;
	char	buffer[1024];
	size_t	bytes_read;

	fd = open("/tmp/error_log.txt", O_RDONLY);
	if (fd == -1)
		return ;
	while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0)
		if (write(STDOUT_FILENO, buffer, bytes_read) == -1)
			break ;
	close(fd);
	fd = open("/tmp/error_log.txt", O_WRONLY | O_TRUNC);
	if (fd == -1)
		return ;
	close (fd);
}

/*
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
*/
