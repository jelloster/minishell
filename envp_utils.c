/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motuomin <motuomin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:46:38 by motuomin          #+#    #+#             */
/*   Updated: 2024/12/09 12:02:31 by motuomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Function : extract_paths
 *
 * Finds the PATH info from envp and returns the paths in an array of strings,
 * or NULL in case of error.
*/

char	**extract_paths(char *envp[])
{
	char	*path_env;
	char	**paths;
	size_t	i;

	i = 0;
	while (envp[i] != NULL && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (envp[i] == NULL)
	{
		paths = malloc(sizeof(char *));
		if (!paths)
			return (NULL);
		paths[0] = NULL;
		return (paths);
	}
	path_env = envp[i] + 5;
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	return (paths);
}

int	update_paths(t_ms *ms)
{
	free_array_of_arrays(ms->paths);
	ms->paths = extract_paths(ms->envp);
	if (!ms->paths)
		return (0);
	return (1);
}
