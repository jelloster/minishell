/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motuomin <motuomin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:46:38 by motuomin          #+#    #+#             */
/*   Updated: 2024/09/11 15:46:54 by motuomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int free_ms(t_ms *ms, char *cmd_line, int ret);

// if threads duplicate memory, they need to be freed there too!!!
int	main(int ac, char *av[], char *envp[])
{
	t_ms	ms;
	char	*cmd_line;
	t_cmd	*cmds;
	pid_t	pid;

	if (!init_ms(ac, av, envp, &ms)) // malloc ms->paths
		return (1);
	while (1)
	{
		// Wait for exe_cmd fork to finish
		waitpid(-1, NULL, 0);

		// Cmd line prompt
		cmd_line = readline("> "); // malloc 2 // add to history
		if (!cmd_line) // does this mean when i dont give anything?
			return (1);
		cmds = parse(cmd_line, &ms); // malloc 3 (cmds)
		if (!cmds)
			return (free_ms(&ms, cmd_line, 1));

		// FORK PROCESS
		pid = fork();
		if (pid == -1)
			exit(0);
		if (pid == 0)
		{
			if (ms.cmd_n == 1)
				exe_cmd(cmds);
			else if (ms.cmd_n != 0 && !pipex(cmds, ms.cmd_n))
				return (1);
		}
		free_cmds(cmds, ms.cmd_n);
		update_history(&ms, cmd_line);
		free(cmd_line);
	}
	free_array_of_arrays(ms.paths);
	free_array_of_arrays(ms.history);
	return (0);
}

int free_ms(t_ms *ms, char *cmd_line, int ret)
{
	if (ms->paths)
	{
		free_array_of_arrays(ms->paths);
		ms->paths = NULL;
	}
	if (cmd_line)
		ft_memdel(&cmd_line);
	return (ret);
}
