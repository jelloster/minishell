/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motuomin <motuomin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:50:35 by motuomin          #+#    #+#             */
/*   Updated: 2025/01/13 18:49:40 by motuomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	child_process(t_cmd cmd, int i, int prev_pipe, t_ms *ms);
static int	iterate_cmds(t_cmd *cmds, pid_t *pids, t_ms *ms);

/*
 * Function : pipex
 * Takes an array of cmd_n command structs (cmds) and executes them using pipes.
*/

int	pipex(t_cmd *cmds, t_ms *ms)
{
	pid_t	*pids;

	pids = malloc(sizeof(pid_t) * ms->cmd_n);
	if (!pids)
		return (0);
	if (!iterate_cmds(cmds, pids, ms))
		return (0);
	return (wait_and_close(pids, ms->cmd_n));
}

static int	forkyforky(t_ms *ms, pid_t *pids, int i)
{
	if (pipe(ms->fds) == -1)
		return (free(pids), 0);
	pids[i] = fork();
	if (pids[i] == -1)
		return (free(pids), 0);
	return (1);
}

static int	iterate_cmds(t_cmd *cmds, pid_t *pids, t_ms *ms)
{
	int	i;
	int	prev_pipe;
	int	ret;

	prev_pipe = -1;
	i = 0;
	while (i < ms->cmd_n)
	{
		if (!forkyforky(ms, pids, i))
			return (0);
		if (pids[i] == 0)
		{
			free(pids);
			ret = child_process(cmds[i], i, prev_pipe, ms);
			exit(free_ms(ms, ms->cmd_line, cmds, ret));
		}
		if (prev_pipe != -1)
			close(prev_pipe);
		if (i < ms->cmd_n - 1)
			prev_pipe = ms->fds[0];
		if (i++ < ms->cmd_n - 1)
			close(ms->fds[1]);
	}
	return (1);
}

static void	pipe_stuff(int i, int prev_pipe, t_cmd cmd, t_ms *ms)
{
	if (i == 0)
	{
		if (cmd.infile && !redirect_input(cmd.infile, &cmd))
			exit(free_ms(ms, ms->cmd_line, ms->cmds, 1));
		dup2(ms->fds[1], STDOUT_FILENO);
	}
	else if (i == ms->cmd_n - 1)
	{
		if (prev_pipe != -1)
			dup2(prev_pipe, STDIN_FILENO);
		if (cmd.outfile && !redirect_output(cmd.outfile, &cmd))
			exit(free_ms(ms, ms->cmd_line, ms->cmds, 1));
	}
	else
	{
		if (prev_pipe != -1)
			dup2(prev_pipe, STDIN_FILENO);
		dup2(ms->fds[1], STDOUT_FILENO);
	}
}

static int	child_process(t_cmd cmd, int i, int prev_pipe, t_ms *ms)
{
	int	ret;

	pipe_stuff(i, prev_pipe, cmd, ms);
	if (prev_pipe != -1)
		close(prev_pipe);
	close(ms->fds[0]);
	close(ms->fds[1]);
	ret = exe_cmd(&cmd, ms);
	if (ret == 69)
		return (exe_built_in(&cmd, ms));
	return (ret);
}
