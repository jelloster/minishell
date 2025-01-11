/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motuomin <motuomin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:49:03 by motuomin          #+#    #+#             */
/*   Updated: 2025/01/11 17:15:41 by motuomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	//g_sig = 0;
}

/*
 * Handles Ctrl+C
*/
void	handle_sigint(int signal)
{
	//printf("sigint parent\n");
	if (signal != SIGINT)
		return ;
	g_sig = signal;
	write(STDERR_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	sigint_child(int signal)
{
	//printf("sigint child\n");
	if (signal != SIGINT)
		return ;
	g_sig = signal;
	printf("g_sig set to %d\n", signal);
	printf("\n");
	exit(130);
}
