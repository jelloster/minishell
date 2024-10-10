/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motuomin <motuomin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:50:35 by motuomin          #+#    #+#             */
/*   Updated: 2024/06/18 13:31:05 by motuomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
    ╔══════════════════════════════════════════╗
    ║                - PIPEX -                 ║
    ║                                          ║
    ║     Replicates the Shell function :      ║
    ║                                          ║
    ║     " < file1 cmd1 | cmd2 > file2 "      ║
    ║                                          ║
    ║          Executed followingly :          ║ 
    ║                                          ║
    ║      ./pipex file1 cmd1 cmd2 file2       ║
    ╚══════════════════════════════════════════╝
*/

#include "pipex.h"

static int	fork_and_exe(t_cmd *cmds, t_aae *aae, int **fds, int cmd_n);
static void	child_process(t_cmd cmd, t_aae *aae, int **fds, int i);
static int	wait_and_close(pid_t *pids, int cmd_n);
static int	free_fds(int **fds, int amount);

int	pipex(t_cmd *cmds, t_aae *aae)
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
		if (pipe(fds[i++]) == -1)
			return (free_fds(fds, i)); // join pipes?
	}
	exit_status = fork_and_exe(cmds, fds, amount + 1); // ?
	free_fds(fds, amount);
	free_memory(cmds);
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
			child_process(cmds[i], aae, fds, i);
		pids[i] = pid;
		if (i > 0)
			close(fds[i - 1][0]);
		if (i++ < cmd_n - 1)
			close(fds[i - 1][1]);
	}
	return (wait_and_close(pids, cmd_n));
}

static void	child_process(t_cmd cmd, t_aae *aae, int **fds, int i)
{
	if (i == 0)
		write_to_pipe(aae->av[1], cmd, fds[i]);
	else if (i == aae->ac - 4)
		read_from_pipe(aae->av[aae->ac - 1], cmd, fds[i - 1][0]);
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
