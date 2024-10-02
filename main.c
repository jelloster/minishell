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


int	main(int ac, char *av[], char *envp[])
{
	t_ms	ms;
	//t_cmd	cmd;
	char	*cmd_line;

	init_ms(ac, av, envp, &ms);

	// Command line loop
	while (1)
	{
		waitpid(-1, NULL, 0);
		cmd_line = readline("> "); // malloc // add to history
		parse(cmd_line, &ms);
		/*
		if(extract_command(cmd_line, &ms, &cmd) == -1)
			return (1); // free mallocs
		exe_cmd(cmd, envp);
		*/
		free(cmd_line);
	}
	return (0);
}
