/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motuomin <motuomin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:46:38 by motuomin          #+#    #+#             */
/*   Updated: 2025/01/11 17:16:14 by motuomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exe_or_pipe(t_ms *ms, t_cmd *cmds);

int	g_sig;

static void	init_terminal_set(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
		exit(EXIT_FAILURE);
	term.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
		exit(EXIT_FAILURE);
}

int	main(int ac, char *av[], char *envp[])
{
	t_ms	ms;
	t_cmd	*cmds;

	init_terminal_set();
	if (!init_ms(ac, av, envp, &ms))
		return (1);
	while (1)
	{
		waitpid(-1, NULL, 0);
		print_and_clear_errorlog();
		handle_signals();
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

void	set_ret_val(t_ms *ms)
{
	if (ms->temp_ret == 69)
		ms->ret_val = exe_built_in(cmds, ms);
	else
		ms->ret_val = ms->temp_ret;
	if (g_sig == SIGINT)
		ms->ret_val = 130;
}

static int	exe_or_pipe(t_ms *ms, t_cmd *cmds)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == -1)
		return (0);
	signal(SIGINT, sigint_aftercat);
	if (pid == 0)
	{
		signal(SIGINT, sigint_child);
		if (ms->cmd_n == 1)
			ms->ret_val = exe_cmd(cmds, ms);
		else if (ms->cmd_n != 0)
			ms->ret_val = pipex(cmds, ms);
		free_ms(ms, ms->cmd_line, cmds, 1);
		exit(ms->ret_val);
	}
	waitpid(pid, &status, 0);
	ms->temp_ret = WEXITSTATUS(status);
	set_ret_val(ms);
	if (access(".heredoc_temp", R_OK == 0))
		unlink(".heredoc_temp");
	if (cmds->infile)
		free(cmds->infile);
	return (free_cmds(cmds, ms->parsed_cmds), 1);
}
