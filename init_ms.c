/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ms.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motuomin <motuomin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:06:53 by motuomin          #+#    #+#             */
/*   Updated: 2025/01/07 21:43:27 by motuomin         ###   ########.fr       */
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
	update_shlvl(ms, 1);
	welcome_msg();
	return (1);
}

/*
 * Function : init_ms_struct
 *
 * Fills the ms struct with basic info.
*/

char	**allocate_and_copy_envp(char **envp, int current_size, int extra_space)
{
	char	**new_envp;
	int		i;

	new_envp = malloc(sizeof(char *) * (current_size + extra_space + 1));
	if (!new_envp)
		return (NULL);
	i = 0;
	while (i < current_size)
	{
		new_envp[i] = strdup(envp[i]); // still reachable (heredoc)?
		if (!new_envp[i])
		{
			while (--i >= 0)
				free(new_envp[i]);
			free(new_envp);
			return (NULL);
		}
		i++;
	}
	while (i < current_size + extra_space)
		new_envp[i++] = NULL;
	new_envp[current_size + extra_space] = NULL;
	return (new_envp);
}

static int	init_ms_struct(char *av[], char *envp[], t_ms *ms)
{
	ms->program_name = av[0];
	ms->nlen = ft_strlen(ms->program_name) - 2;
	ms->envp = allocate_and_copy_envp(envp, count_env(envp), 0);
	if (!ms->envp)
		return (0);
	ms->cmd_n = 0;
	ms->error = 0;
	ms->parsed_cmds = 0;
	ms->ret_val = 0;
	ms->cmds = NULL;
	ms->paths = extract_paths(envp);
	ms->shell_vars = NULL;
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

void	update_shlvl(t_ms *ms, int sign)
{
	char	*shlvl_str;
	int		shlvl;

	shlvl_str = get_env_value(ms, "SHLVL", 5);
	if (shlvl_str)
		shlvl = ft_atoi(shlvl_str);
	else
		shlvl = 0;
	if (shlvl < 0)
	{
		shlvl = 0;
	}
	shlvl += sign;
	shlvl_str = ft_itoa(shlvl);
	if (!shlvl)
		return ;
	setenv_update("SHLVL", shlvl_str, ms);
	free(shlvl_str);
}

static void	welcome_msg(void)
{
	clear_terminal();
	print_in_color(WELCOME_MSG, BLUE);
}
