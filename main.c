/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motuomin <motuomin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:46:38 by motuomin          #+#    #+#             */
/*   Updated: 2024/10/28 14:47:22 by motuomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_ms(t_ms *ms, char *cmd_line, t_cmd *cmds, int ret);
int	exe_or_pipe(t_ms *ms, t_cmd *cmds);
void	err(t_ms *ms);

// if threads duplicate memory, they need to be freed there too!!!
int	main(int ac, char *av[], char *envp[])
{
	t_ms	ms;
	t_cmd	*cmds;

	if (!init_ms(ac, av, envp, &ms))
		return (1);
	while (1)
	{
		waitpid(-1, NULL, 0);
		ms.cmd_line = readline("> "); // malloc 2
		if (ms.cmd_line)
			add_history(ms.cmd_line);
		if (!ms.cmd_line)
			return (1);
		cmds = parse(ms.cmd_line, &ms); // malloc 3 (cmds)
		if (!cmds)
			err(&ms);
		if (!ms.error)
			exe_or_pipe(&ms, cmds);
		free(ms.cmd_line);
		ms.error = 0;
	}
	return (free_ms(&ms, NULL, cmds, 0));
}

void	err(t_ms *ms)
{
	printf("Error.\n");
	ms->error = 1;
}

int	exe_or_pipe(t_ms *ms, t_cmd *cmds)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		exit(0);
	if (pid == 0)
	{
		if (ms->cmd_n == 1)
			exe_cmd(cmds);
		else if (ms->cmd_n != 0)
			pipex(cmds, ms->cmd_n);
		free_ms(ms, ms->cmd_line, cmds, 1);
		exit(1);
	}
	free_cmds(cmds, ms->cmd_n);
	return (0);
}

int	free_ms(t_ms *ms, char *cmd_line, t_cmd *cmds, int ret)
{
	if (ms->paths)
	{
		free_array_of_arrays(ms->paths);
		ms->paths = NULL;
	}
	if (ms->history)
	{
		free_array_of_arrays(ms->history);
		ms->history = NULL;
	}
	if (cmds)
	{
		free_cmds(cmds, ms->cmd_n);
	}
	if (cmd_line)
		ft_memdel(&cmd_line);
	return (ret);
}
