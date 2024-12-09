/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motuomin <motuomin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:46:38 by motuomin          #+#    #+#             */
/*   Updated: 2024/12/09 17:11:41 by motuomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exe_or_pipe(t_ms *ms, t_cmd *cmds);

t_sig	g_sig;

int	main(int ac, char *av[], char *envp[])
{
	t_ms	ms;
	t_cmd	*cmds;

	handle_signals();

	if (!init_ms(ac, av, envp, &ms))
		return (1);
	while (1)
	{
		// Wait for execution threads to finish
		waitpid(-1, NULL, 0);
		print_and_clear_errorlog();

		// Prompt
		ms.cmd_line = readline("$ ");
		//ms.cmd_line = readline("");

		// Add to history
		if (ms.cmd_line)
			add_history(ms.cmd_line); // how to free this?
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
	int	status;

	pid = fork();
	if (pid == -1)
		return(0);
	g_sig.child = 0;
	if (pid == 0)
	{
		g_sig.child = 1;
		if (ms->cmd_n == 1)
			ms->ret_val = exe_cmd(cmds, ms);
		else if (ms->cmd_n != 0)
			ms->ret_val = pipex(cmds, ms);
		free_ms(ms, ms->cmd_line, cmds, 1);
		exit(ms->ret_val); // Exit value? // Should whole process stop ??
	}
	waitpid(pid, &status, 0);
	ms->temp_ret = WEXITSTATUS(status);
	//printf("temp ret = %d.\n", ms->temp_ret);
	if (ms->temp_ret == 69)
		ms->ret_val = exe_built_in(cmds, ms); // built in
	else
		ms->ret_val = ms->temp_ret;
	// Free parsed cmds
	free_cmds(cmds, ms->parsed_cmds);
	return (1);
}
