/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motuomin <motuomin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:46:38 by motuomin          #+#    #+#             */
/*   Updated: 2025/01/07 20:09:05 by motuomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_write(const char *delim, t_cmd *cmd)
{
	int		temp_fd;
	char	*line;
	int		pid;
	int		status;
	

	pid = fork();
	if (pid == -1)
		return (0);

	// child
	if (pid == 0)
	{
		temp_fd = open(".heredoc_temp", O_WRONLY | O_CREAT | O_TRUNC, 0600);
		if (temp_fd == -1)
			return (perror("open write"), 0);
		g_sig.in_heredoc = 1;
		while (1)
		{
			line = readline("> ");
			if (!line || strcmp(line, delim) == 0)
			{
				free(line);
				exit (0);
			}
			write(temp_fd, line, strlen(line));
			write(temp_fd, "\n", 1);
			free(line);
		}
		close(temp_fd);
		exit (1);
	}
	else
	{
		waitpid(pid, &status, 0);
		//printf("Child done\n");
		cmd->inredir = STD_IN;
		cmd->infile = ".heredoc_temp"; // ?
		g_sig.in_heredoc = 0;
		if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
		{
			/*
			if (status == 130)
				printf("Signal???\n");
			if (WIFEXITED(status) == 0)
				printf("Exited with 0\nn");
			printf("A\n"); */
			if (access(".heredoc_temp", R_OK == 0))
				unlink(".heredoc_temp");
		}
	}
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
