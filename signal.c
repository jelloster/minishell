/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motuomin <motuomin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:49:03 by motuomin          #+#    #+#             */
/*   Updated: 2024/12/09 12:08:02 by motuomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sig_init(void)
{
	g_sig.sigint = 0;
	g_sig.sigquit = 0;
	g_sig.child = 0;
	g_sig.exit_status = 0;
}

void	handle_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sig_init();
	sa_int.sa_handler = handle_sigint;
	sa_int.sa_flags = SA_RESTART;
	sigemptyset(&sa_int.sa_mask);
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_handler = handle_sigquit;
	sa_quit.sa_flags = 0;
	sigemptyset(&sa_quit.sa_mask);
	sigaction(SIGQUIT, &sa_quit, NULL);
}

void	handle_sigint(int signal)
{
	(void)signal;
	if (!g_sig.child)
	{
		write(STDERR_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_sig.exit_status = 1;
	}
	else
	{
		printf("\n");
		g_sig.exit_status = 130;
	}
	g_sig.sigint = 1;
}

void	handle_sigquit(int signal)
{
	(void)signal;
}
