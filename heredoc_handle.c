/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motuomin <motuomin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:46:38 by motuomin          #+#    #+#             */
/*   Updated: 2025/01/18 16:19:06 by jkarhu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	child_process(const char *delim, t_ms *ms)
{
	int		temp_fd;
	char	*line;
	char	*heredoc_name;

	heredoc_name = ft_itoa((int)getpid());
	temp_fd = open(heredoc_name, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	free(heredoc_name);
	if (temp_fd == -1)
		return (perror("open write"), 0);
	signal(SIGINT, sigint_child);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strncmp(line, delim, ft_strlen(delim) + 1) == 0)
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

static void	parent_process(t_ms *ms, t_cmd *cmd, int pid, int *status)
{
	int		child_pid;
	char	*hd_name;

	child_pid = (int)waitpid(pid, status, 0);
	hd_name = ft_itoa(child_pid);
	if (!hd_name)
		exit(free_ms(ms, ms->cmd_line, ms->cmds, 1));
	cmd->inredir = STD_IN;
	if (cmd->infile)
	{
		unlink(cmd->infile);
		free(cmd->infile);
	}
	cmd->infile = hd_name;
	cmd->hd = 1;
	if (WIFEXITED(*status) && WEXITSTATUS(*status) == 0)
		if (access(hd_name, R_OK == 0))
			unlink(hd_name);
	if (WEXITSTATUS(*status) == 130)
		ms->dont = 1;
}

int	heredoc_write(const char *delim, t_ms *ms, t_cmd *cmd)
{
	int		status;
	int		pid;

	status = 0;
	pid = fork();
	if (pid == -1)
		return (0);
	signal(SIGINT, SIG_IGN);
	if (pid == 0)
	{
		if (!child_process(delim, ms))
			return (0);
	}
	else
		parent_process(ms, cmd, pid, &status);
	return (WEXITSTATUS(status));
}
