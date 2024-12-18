/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_built_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motuomin <motuomin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:35:49 by motuomin          #+#    #+#             */
/*   Updated: 2024/12/16 12:57:48 by motuomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_built_in(char **args, t_ms *ms)
{
	char	cwd[1024];
	char	*home;

	if (!args[1])
	{
		home = getenv("HOME");
		if (!home)
			return (perror("HOME env"), 1);
		if (chdir(home) == -1)
			return (perror("cd"), 1);
	}
	else
	{
		if (args[2])
		{
			write(STDERR_FILENO, ms->program_name + 2, ms->nlen);
			write(STDERR_FILENO, ": cd: too many arguments\n", 25);
		}
		if (chdir(args[1]) == -1)
			return (perror("cd"), 1);
	}
	if (getcwd(cwd, sizeof(cwd)))
		setenv_update("PWD", cwd, ms->envp);
	return (0);
}
