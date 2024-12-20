/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motuomin <motuomin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:50:35 by motuomin          #+#    #+#             */
/*   Updated: 2024/12/16 14:08:00 by motuomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	child_process(t_cmd cmd, int i, int prev_pipe, t_ms *ms);
static int	wait_and_close(pid_t *pids, int cmd_n);
static int	free_and_ret(void *ptr, int ret);

/*
 * Function : pipex
 * Takes an array of cmd_n command structs (cmds) and executes them using pipes.
*/

// amount of pipes : ms->cmd_n - 1

int	pipex(t_cmd *cmds, t_ms *ms)
{
	int		i;
	int		prev_pipe;
	pid_t	*pids;

	prev_pipe = -1;
	pids = malloc(sizeof(pid_t) * ms->cmd_n);
	if (!pids)
		return (0);
	i = 0;
	while (i < ms->cmd_n)
	{
		if (pipe(ms->fds) == -1)
			return (free_and_ret(pids, 0));
		pids[i] = fork();
		if (pids[i] == -1)
			return (free_and_ret(pids, 0));
		if (pids[i] == 0)
			child_process(cmds[i], i, prev_pipe, ms);
		if (prev_pipe != -1)
			close(prev_pipe);
		if (i < ms->cmd_n - 1)
			prev_pipe = ms->fds[0];
		if (i++ < ms->cmd_n - 1)
			close(ms->fds[1]);
	}
	return (wait_and_close(pids, ms->cmd_n));
}

static void	child_process(t_cmd cmd, int i, int prev_pipe, t_ms *ms)
{
	if (i == 0)
	{
		if (cmd.infile && !redirect_input(cmd.infile, &cmd))
			exit(1);
		dup2(ms->fds[1], STDOUT_FILENO);
	}
	else if (i == ms->cmd_n - 1)
	{
		if (prev_pipe != -1)
			dup2(prev_pipe, STDIN_FILENO);
		if (cmd.outfile && !redirect_output(cmd.outfile, &cmd))
			exit(1);
	}
	else
	{
		if (prev_pipe != -1)
			dup2(prev_pipe, STDIN_FILENO);
		dup2(ms->fds[1], STDOUT_FILENO);
	}
	if (prev_pipe != -1)
		close(prev_pipe);
	close(ms->fds[0]);
	close(ms->fds[1]);
	if (exe_cmd(&cmd, ms) == 69)
		exe_built_in(&cmd, ms);
	exit(1);
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

static int	free_and_ret(void *ptr, int ret)
{
	free (ptr);
	return (ret);
}
