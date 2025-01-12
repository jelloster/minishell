/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motuomin <motuomin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:46:38 by motuomin          #+#    #+#             */
/*   Updated: 2025/01/11 17:06:13 by motuomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	child_process(const char *delim, t_ms *ms)
{
	int		temp_fd;
	char	*line;

	temp_fd = open(".heredoc_temp", O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (temp_fd == -1)
		return (perror("open write"), 0);
	signal(SIGINT, sigint_child);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strncmp(line, delim, ft_strlen(delim)) == 0)
		{
			free(line);
			free_array_of_arrays(ms->split);
			exit(free_ms(ms, ms->cmd_line, ms->cmds, 1));
		}
		write(temp_fd, line, strlen(line));
		write(temp_fd, "\n", 1);
		free(line);
	}
	return (1);
}

int	heredoc_write(const char *delim, t_ms *ms, t_cmd *cmd)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == -1)
		return (0);
	status = 0;
	signal(SIGINT, SIG_IGN);
	if (pid == 0)
	{
		if (!child_process(delim, ms))
			return (0);
	}
	else
	{
		waitpid(pid, &status, 0);
		cmd->inredir = STD_IN;
		cmd->infile = ".heredoc_temp";
		if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
			if (access(".heredoc_temp", R_OK == 0))
				unlink(".heredoc_temp");
	}
	return (WEXITSTATUS(status));
}
