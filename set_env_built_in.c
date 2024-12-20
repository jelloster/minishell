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

char **expand_envp(char **envp, int current_size, int extra_space)
{
    char **new_envp;
    int i;

    new_envp = malloc(sizeof(char *) * (current_size + extra_space + 1));
    if (!new_envp)
        return (NULL);
    i = 0;
    while (i < current_size)
    {
        new_envp[i] = envp[i];
        i++;
    }
    while (i < current_size + extra_space)
    {
        new_envp[i] = NULL;
        i++;
    }
    new_envp[current_size + extra_space] = NULL;
    free(envp);
    return (new_envp);
}

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

int	setenv_update(const char *key, const char *value, char **envp)
{
	int		i;
	char	*temp;
	char	*new_entry;

	new_entry = ft_strjoin(key, "=");
	if (!new_entry)
		return (-1);
	temp = ft_strjoin(new_entry, value);
	free(new_entry);
	if (!temp)
		return (-1);
	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], key, ft_strlen(key))
			&& envp[i][ft_strlen(key)] == '=')
		{
			free(envp[i]);
			envp[i] = temp;
			return (0);
		}
	}
	envp[count_env(envp)] = temp;
	envp[count_env(envp) + 1] = NULL;
	return (0);
}
