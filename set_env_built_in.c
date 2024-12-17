/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env_built_in.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motuomin <motuomin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:54:41 by motuomin          #+#    #+#             */
/*   Updated: 2024/12/16 13:00:52 by motuomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(t_ms *ms, const char *key, int custom_len)
{
	int		i;
	size_t	key_len;

	i = 0;
	if (custom_len)
	{
		key_len = custom_len;
	}
	else
		key_len = ft_strlen(key);
	while (ms->envp[i])
	{
		if (!ft_strncmp(ms->envp[i], key, key_len)
			&& ms->envp[i][key_len] == '=')
			return (ms->envp[i] + key_len + 1);
		i++;
	}
	return (NULL);
}

/*
char	*free_on_error(char **split_words, char *result)
{
	free_array_of_arrays(split_words);
	free(result);
	return (NULL);
}*/

int	setenv_update(const char *key, const char *value, char **envp)
{
	int		i;
	int		env_len;
	size_t	key_len;
	char	*temp;
	char	*new_entry;

	key_len = ft_strlen(key);
	new_entry = ft_strjoin(key, "=");
	if (!new_entry)
		return (-1);
	temp = ft_strjoin(new_entry, value);
	free(new_entry);
	if (!temp)
		return (-1);
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], key, key_len) && envp[i][key_len] == '=')
		{
			envp[i] = temp;
			return (0);
		}
		i++;
	}
	env_len = strstrlen(envp);
	envp[env_len] = temp;
	envp[env_len + 1] = NULL;
	return (0);
}
