/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ms.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motuomin <motuomin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:06:53 by motuomin          #+#    #+#             */
/*   Updated: 2024/12/09 19:05:03 by jkarhu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_ms_struct(char *av[], char *envp[], t_ms *ms);
static void	welcome_msg(void);

/*
 * Function : init_ms
 *
 * Calls the init_ms_struct function, clears the terminal,
 * and prints a welcome message.
*/

int	init_ms(int ac, char *av[], char *envp[], t_ms *ms)
{
	if (ac != 1)
		return (0);
	if (!init_ms_struct(av, envp, ms))
		return (0);
	welcome_msg();
	return (1);
}

/*
 * Function : init_ms_struct
 *
 * Fills the ms struct with basic info.
*/

static int	init_ms_struct(char *av[], char *envp[], t_ms *ms)
{
	ms->program_name = av[0];
	ms->envp = envp;
	ms->cmd_n = 0;
	ms->error = 0;
	ms->parsed_cmds = 0;
	ms->ret_val = 0;
	ms->cmds = NULL;
	ms->paths = extract_paths(envp);
	ms->shell_vars = NULL;
	init_shell_vars(envp, &ms->shell_vars);
	if (!ms->paths)
		return (0);
	return (1);
}

/*
 * Function : welcome_msg
 *
 * Clears the terminal and prints out a welcome message.
 * (Welcome message defined in minishell.h)
*/

static void	welcome_msg(void)
{
	clear_terminal();
//	print_in_color(WELCOME_MSG, BLUE);
}
