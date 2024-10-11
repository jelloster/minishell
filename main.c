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

// if threads duplicate memory, they need to be freed there too!!!
int	main(int ac, char *av[], char *envp[])
{
	t_ms	ms;
	char	*cmd_line;
	t_cmd	*cmds;

	init_ms(ac, av, envp, &ms);
	while (1)
	{
		waitpid(-1, NULL, 0);
		cmd_line = readline("> "); // malloc // add to history
		cmds = parse(cmd_line, &ms);
		if (! cmds)
			return (1);
		if (ms.cmd_n == 1)
			exe_cmd(cmds);
		else if (ms.cmd_n != 0 && !pipex(cmds, ms.cmd_n))
			return (1);
		free_cmds(cmds, ms.cmd_n);
	}
	// free ms
	free_array_of_arrays(ms.paths);
	return (0);
}
