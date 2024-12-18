/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motuomin <motuomin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:46:38 by motuomin          #+#    #+#             */
/*   Updated: 2024/12/16 13:38:20 by motuomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_write(const char *delim, t_cmd *cmd)
{
	int		temp_fd;
	char	*line;

	temp_fd = open(".heredoc_temp", O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (temp_fd == -1)
	{
		perror("open write");
		return (0);
	}
	while (1)
	{
		line = readline("> ");
		if (!line || strcmp(line, delim) == 0)
		{
			free(line);
			break ;
		}
		write(temp_fd, line, strlen(line));
		write(temp_fd, "\n", 1);
		free(line);
	}
	close(temp_fd);
	cmd->inredir = STD_IN;
	cmd->infile = ft_strdup(".heredoc_temp");
	return (1);
}

int	heredoc_print(t_cmd *cmd)
{
	int		fd;
	char	*line;

	fd = open(cmd->infile, O_RDONLY);
	if (fd == -1)
	{
		perror("open print");
		return (0);
	}
	line = get_next_line(fd);
	while (line)
	{
		ft_printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (1);
}
