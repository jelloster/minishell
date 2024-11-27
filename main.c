/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motuomin <motuomin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:46:38 by motuomin          #+#    #+#             */
/*   Updated: 2024/11/04 16:06:40 by motuomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exe_or_pipe(t_ms *ms, t_cmd *cmds);

int	main(int ac, char *av[], char *envp[])
{
	t_ms	ms;
	t_cmd	*cmds;

	if (!init_ms(ac, av, envp, &ms))
		return (1);
	while (1)
	{
		// Wait for execution threads to finish
		waitpid(-1, NULL, 0);

		// Prompt
		ms.cmd_line = readline("> ");

		// Add to history
		if (ms.cmd_line)
			add_history(ms.cmd_line);
		else
			return (free_ms(&ms, ms.cmd_line, NULL, 1));

		// Parse command line into an array of t_cmd structs.
		cmds = parse(ms.cmd_line, &ms);
		if (!cmds)
			err(&ms);

		// Execute commands if there was no error in parsing
		if (!ms.error)
			if(!exe_or_pipe(&ms, cmds))
				return (free_ms(&ms, ms.cmd_line, cmds, 1));

		// Reset
		free(ms.cmd_line);
		ms.error = 0;
	}
	return (free_ms(&ms, NULL, cmds, 0));
}

static int	exe_or_pipe(t_ms *ms, t_cmd *cmds)
{
	int	pid;

	// Fork the process into main process and executable
	pid = fork();
	if (pid == -1)
		return(0);

	// Executing (child) fork
	if (pid == 0)
	{
		// If there is just 1 cmd, execute it
		if (ms->cmd_n == 1)
			ms->ret_val = exe_cmd(cmds, ms);

		// Otherwise use pipex
		else if (ms->cmd_n != 0)
		{
			//ft_printf("pipes disabled for testingf");
			ms->ret_val = pipex(cmds, ms); // doesn't work cause fork not thread (threads not allowed)
		}

		// If the execve fails, free memory and exit
		free_ms(ms, ms->cmd_line, cmds, 1);
		exit(1); // Exit value? // Should whole process stop ??
	}
	// Free parsed cmds
	free_cmds(cmds, ms->parsed_cmds);
	return (1);
}
