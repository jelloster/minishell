/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motuomin <motuomin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:46:38 by motuomin          #+#    #+#             */
/*   Updated: 2024/12/16 13:38:20 by motuomin         ###   ########.fr       */
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
		waitpid(-1, NULL, 0);
		g_sig.child = 0;
		print_and_clear_errorlog();
		ms.cmd_line = readline("$ ");
		if (ms.cmd_line)
			add_history(ms.cmd_line);
		else
			return (free_ms(&ms, ms.cmd_line, NULL, 0));
		cmds = parse(ms.cmd_line, &ms);
		if (cmds)
			if (!exe_or_pipe(&ms, cmds))
				return (free_ms(&ms, ms.cmd_line, cmds, 1));
		free(ms.cmd_line);
	}
	return (free_ms(&ms, NULL, cmds, 0));
}

static int	exe_or_pipe(t_ms *ms, t_cmd *cmds)
{
	int	pid;
	int	status;

	g_sig.child = 1;
	pid = fork();
	if (pid == -1)
		return (0);
	if (pid == 0)
	{
		if (ms->cmd_n == 1)
			ms->ret_val = exe_cmd(cmds, ms);
		else if (ms->cmd_n != 0)
			ms->ret_val = pipex(cmds, ms);
		free_ms(ms, ms->cmd_line, cmds, 1);
		exit(ms->ret_val);
	}
	waitpid(pid, &status, 0);
	ms->temp_ret = WEXITSTATUS(status);
	if (ms->temp_ret == 69)
		ms->ret_val = exe_built_in(cmds, ms);
	else
		ms->ret_val = ms->temp_ret;
	free_cmds(cmds, ms->parsed_cmds);
	return (1);
}
