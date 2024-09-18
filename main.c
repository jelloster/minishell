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

void	exe_cmd(t_cmd cmd, char *envp[]);

int	main(int ac, char *av[], char *envp[])
{
	t_ms	ms;
	t_cmd	cmd;
	char	*cmd_line;

	if (!parse(ac, av, envp, &ms))
		return (1);
	printf("\033[H\033[J");
	printf(BLUE "\n ✧.* Welcome to MINISHELL! ✧.*\n\n" RESET);
	while (1)
	{
		waitpid(-1, NULL, 0);
		cmd_line = readline("> "); // malloc // add to history
		if(extract_command(cmd_line, &ms, &cmd) == -1)
			return (1); // free mallocs
		exe_cmd(cmd, envp);
		free(cmd_line);
	}
	return (0);
}

void	exe_cmd(t_cmd cmd, char *envp[])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
	{
		if (access(cmd.pathed_cmd, X_OK) == 0)
			execve(cmd.pathed_cmd, cmd.args, envp);
	}
}
