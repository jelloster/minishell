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
	*t_fd = open(".error_log", O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (*t_fd == -1)
	{
		perror("Failed to open/create error log");
		return (0);
	}
	*original_fd = dup(STDOUT_FILENO);
	if (*original_fd == -1)
	{
		close(*t_fd);
		return (0);
	}
	if (dup2(*t_fd, STDOUT_FILENO) == -1)
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
		printf("%s", str);
	if (error == FILE_NOT_FOUND)
		printf(": No such file or directory");
	else if (error == COMMAND_NOT_FOUND)
		printf(": command not found");
	else if (error == PERMISSION_DENIED)
	{
		printf("permission denied: ");
		if (str)
			printf("%s", str);
	}
	else if (error == IS_DIRECTORY)
	{
		printf("is a directory: ");
		if (str)
			printf("%s", str);
	}
	printf("\n");
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
	printf("%s", b);
	printf(": ");
	write_error_msg(error, str);
	if (dup2(original_fd, STDOUT_FILENO) == -1)
		perror("Failed to reset stderr");
	close(temp_fd);
	close(original_fd);
}

void	delete_error_log(void)
{
	if (access(".error_log", R_OK == 0))
		unlink(".error_log");
}

void	print_and_clear_errorlog(void)
{
	int		fd;
	char	buffer[1024];
	size_t	bytes_read;

	fd = open(".error_log", O_RDONLY);
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
	unlink(".error_log");
}
