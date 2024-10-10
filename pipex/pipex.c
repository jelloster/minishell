/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motuomin <motuomin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:50:35 by motuomin          #+#    #+#             */
/*   Updated: 2024/10/10 14:25:32 by motuomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	fork_and_exe(t_cmd *cmds, int **fds, int cmd_n);
static void	child_process(t_cmd cmd, int **fds, int i, int amount);
static int	wait_and_close(pid_t *pids, int cmd_n);
static int	free_fds(int **fds, int amount);

int	pipex(t_cmd *cmds, int amount)
{
	int	**fds;
	int	i;
	int	exit_status;

	fds = malloc(amount * sizeof(int *));
	if (!fds)
		return (0);
	i = 0;
	while (i < amount)
	{
		fds[i] = malloc(2 * sizeof(int));
		if (!fds[i])
			return (free_fds(fds, i));
		if (pipe(fds[i]) == -1)
			return (free_fds(fds, i)); // join pipes?
		i++;
	}
	exit_status = fork_and_exe(cmds, fds, amount + 1);
	free_fds(fds, amount);
	return (exit_status);
}

static int	fork_and_exe(t_cmd *cmds, int **fds, int cmd_n)
{
	int		i;
	pid_t	pid;
	pid_t	*pids;

	pids = malloc(sizeof(pid_t) * cmd_n);
	if (!pids)
		return (0);
	i = 0;
	while (i < cmd_n)
	{
		pid = fork();
		if (pid == -1)
		{
			free(pids);
			return (0);
		}
		if (pid == 0)
			child_process(cmds[i], fds, i, cmd_n);
		pids[i] = pid;
		if (i > 0)
			close(fds[i - 1][0]);
		if (i++ < cmd_n - 1)
			close(fds[i - 1][1]);
	}
	return (wait_and_close(pids, cmd_n));
}

static void	child_process(t_cmd cmd, int **fds, int i, int amount)
{
	if (i == 0)
		write_to_pipe(cmd, fds[i]); // no input file always
	else if (i == amount)
		read_from_pipe(cmd, fds[i - 1][0]); // no  output file always
	else
		read_and_write(cmd, fds[i - 1][0], fds[i][1]);
}

static int	wait_and_close(pid_t *pids, int cmd_n)
{
	int	exit_status;
	int	last_status;
	int	i;

	i = 0;
	last_status = 0;
	while (i < cmd_n)
	{
		waitpid(pids[i], &exit_status, 0);
		if (WIFEXITED(exit_status))
			last_status = WEXITSTATUS(exit_status);
		i++;
	}
	free(pids);
	return (last_status);
}

static int	free_fds(int **fds, int amount)
{
	int	i;

	i = 0;
	if (fds)
	{
		while (i < amount)
		{
			if (fds[i])
			{
				free (fds[i]);
				fds[i] = NULL;
			}
			i++;
		}
		free (fds);
		fds = NULL;
	}
	return (0);
}
