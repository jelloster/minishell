/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_built_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motuomin <motuomin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:37:18 by motuomin          #+#    #+#             */
/*   Updated: 2024/12/16 11:37:53 by motuomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	unsetenv_manual(const char *key, char **envp)
{
	int		i;
	int		j;
	size_t	key_len;

	i = 0;
	key_len = ft_strlen(key);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, key_len) == 0 && (envp[i][key_len] == '='
			|| envp[i][key_len] == '\0'))
		{
			free(envp[i]);
			j = i;
			while (envp[j + 1])
			{
				envp[j] = envp[j + 1];
				j++;
			}
			envp[j] = NULL;
			return (0);
		}
		i++;
	}
	return (1);
}

int	unset_built_in(char **args, t_ms *ms)
{
	int	i;

	if (!args[1])
	{
		perror("unset");
		return (1);
	}
	i = 1;
	while (args[i])
	{
		unsetenv_manual(args[i], ms->envp);
		if (find_shell_var(ms->shell_vars, args[i]))
			remove_shell_var(&ms->shell_vars, args[i]);
		i++;
	}
	return (0);
}
