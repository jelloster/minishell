/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motuomin <motuomin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:49:03 by motuomin          #+#    #+#             */
/*   Updated: 2025/01/07 21:41:59 by motuomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sig_init(void)
{
	g_sig.sigint = 0;
	g_sig.sigquit = 0;
	g_sig.child = 0;
	g_sig.exit_status = 0;
	g_sig.in_heredoc = 0;
	g_sig.im_heredoc = 0;
}

void	handle_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sig_init();
	sa_int.sa_handler = handle_sigint;
	sa_int.sa_flags = 0;
	sigemptyset(&sa_int.sa_mask);
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_handler = SIG_IGN;
	sa_quit.sa_flags = 0;
	sigemptyset(&sa_quit.sa_mask);
	sigaction(SIGQUIT, &sa_quit, NULL);
}

/*
 * Handles Ctrl+C
*/
void	handle_sigint(int signal)
{
	(void)signal;
	g_sig.sigint = 1;
	if (g_sig.in_heredoc && g_sig.im_heredoc)
	{
		g_sig.exit_status = 130;
		write(STDERR_FILENO, "\n", 1);
		exit(130);
	}
	else if (g_sig.in_heredoc)
		g_sig.exit_status = 130;
	else if (!g_sig.child)
	{
		write(STDERR_FILENO, "\n", 1);
		g_sig.exit_status = 1;
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else
	{
		printf("\n");
		g_sig.exit_status = 130;
	}
}

void	signal_check(t_ms *ms)
	{
	if (g_sig.sigint)
	{
		ms->ret_val = 130;
		g_sig.sigint = 0;
	}
	else if (g_sig.sigquit)
	{
		ms->ret_val = 131;
		g_sig.sigquit = 0;
	}
}
