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

static char	*create_new_entry(const char *key, const char *value)
{
	char	*temp;
	char	*new_entry;

	new_entry = ft_strjoin(key, "=");
	if (!new_entry)
		return (NULL);
	temp = ft_strjoin(new_entry, value);
	free(new_entry);
	return (temp);
}

static int	update_existing_entry(t_ms *ms, const char *key, char *temp)
{
	int	i;

	i = 0;
	while (ms->envp[i])
	{
		if (!ft_strncmp(ms->envp[i], key, ft_strlen(key))
			&& ms->envp[i][ft_strlen(key)] == '=')
		{
			free(ms->envp[i]);
			ms->envp[i] = temp;
			return (1);
		}
		i++;
	}
	return (0);
}

static int	expand_and_add_entry(t_ms *ms, char *temp, int env_count)
{
	char	**new_envp;
	int		i;

	new_envp = allocate_and_copy_envp(ms->envp, env_count, 1);
	if (!new_envp)
	{
		free(temp);
		return (-1);
	}
	new_envp[env_count] = temp;
	new_envp[env_count + 1] = NULL;
	i = 0;
	while (ms->envp[i])
		free(ms->envp[i++]);
	free(ms->envp);
	ms->envp = new_envp;
	return (0);
}

int	setenv_update(const char *key, const char *value, t_ms *ms)
{
	char	*temp;
	int		env_count;

	temp = create_new_entry(key, value);
	if (!temp)
		return (-1);
	if (update_existing_entry(ms, key, temp))
		return (0);
	env_count = count_env(ms->envp);
	return (expand_and_add_entry(ms, temp, env_count));
}
