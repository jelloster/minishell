/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ms.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motuomin <motuomin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:06:53 by motuomin          #+#    #+#             */
/*   Updated: 2024/11/04 16:07:06 by motuomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_ms_struct(char *av[], char *envp[], t_ms *ms);
static void	welcome_msg(void);

int	init_ms(int ac, char *av[], char *envp[], t_ms *ms)
{
	if (ac != 1)
		return (0);
	if(!init_ms_struct(av, envp, ms))
		return (0);
	welcome_msg();
	return (1);
}

static int	init_ms_struct(char *av[], char *envp[], t_ms *ms)
{
	ms->program_name = av[0];
	ms->envp = envp;
	ms->cmd_n = 0;
	ms->error = 0;
	ms->parsed_cmds = 0;
	ms->paths = extract_paths(envp); // malloc 1
	if (!ms->paths)
		return (0);
	return (1);
}

static void	welcome_msg(void)
{
	clear_terminal();
	print_in_color(WELCOME_MSG, BLUE);
}
