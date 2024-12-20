/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motuomin <motuomin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:46:38 by motuomin          #+#    #+#             */
/*   Updated: 2024/12/16 13:38:20 by motuomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	setup_error_log(int *original_fd, int *t_fd)
{
	*t_fd = open("/tmp/error_log.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (*t_fd == -1)
		return (0);
	*original_fd = dup(STDERR_FILENO);
	if (*original_fd == -1)
	{
		close(*t_fd);
		return (0);
	}
	if (dup2(*t_fd, STDERR_FILENO) == -1)
	{
		close(*t_fd);
		close(*original_fd);
		return (0);
	}
	return (1);
}

static void	write_error_msg(int error, char *str)
{
	if (str && error != PERMISSION_DENIED && error != IS_DIRECTORY)
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
	else if (error == IS_DIRECTORY)
	{
		ft_putstr_fd("is a directory: ", STDERR_FILENO);
		if (str)
			ft_putstr_fd(str, STDERR_FILENO);
	}
	ft_putstr_fd("\n", STDERR_FILENO);
}

void	error_msg(int error, char *str, char *binary)
{
	int		temp_fd;
	int		original_fd;
	char	*b;

	if (!setup_error_log(&original_fd, &temp_fd))
		return ;
	if (ft_strchr(binary, '/'))
		b = binary + ((ft_strrchr(binary, '/') + 1) - binary);
	else
		b = binary;
	ft_putstr_fd(b, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	write_error_msg(error, str);
	if (dup2(original_fd, STDERR_FILENO) == -1)
		perror("Failed to reset stderr");
	close(temp_fd);
	close(original_fd);
}

void	print_and_clear_errorlog(void)
{
	int		fd;
	char	buffer[1024];
	size_t	bytes_read;

	fd = open("/tmp/error_log.txt", O_RDONLY);
	if (fd == -1)
		return ;
	bytes_read = read(fd, buffer, sizeof(buffer));
	while (bytes_read > 0)
	{
		if (write(STDOUT_FILENO, buffer, bytes_read) == -1)
			break ;
		bytes_read = read(fd, buffer, sizeof(buffer));
	}
	close(fd);
	fd = open("/tmp/error_log.txt", O_WRONLY | O_TRUNC);
	if (fd == -1)
		return ;
	close (fd);
}
