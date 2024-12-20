/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motuomin <motuomin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:46:38 by motuomin          #+#    #+#             */
/*   Updated: 2024/12/16 13:38:20 by motuomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

static void	copy_env(char **sorted_env, char **msenvp, int env_count)
{
	int	i;

	i = 0;
	while (i < env_count)
	{
		sorted_env[i] = strdup(msenvp[i]);
		if (!sorted_env[i])
		{
			perror("strdup");
			while (--i >= 0)
				free(sorted_env[i]);
			free(sorted_env);
			return ;
		}
		i++;
	}
	sorted_env[env_count] = NULL;
}

static int	count_env(char **msenvp)
{
	int	count;

	count = 0;
	while (msenvp[count])
		count++;
	return (count);
}

static void	bubble_sort_env(char **env, int env_count)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (i < env_count - 1)
	{
		j = 0;
		while (j < env_count - i - 1)
		{
			if (ft_strcmp(env[j], env[j + 1]) > 0)
			{
				temp = env[j];
				env[j] = env[j + 1];
				env[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

char	**sort_env(char **msenvp)
{
	int		env_count;
	char	**sorted_env;

	env_count = count_env(msenvp);
	sorted_env = malloc(sizeof(char *) * (env_count + 1));
	if (!sorted_env)
		return (NULL);
	copy_env(sorted_env, msenvp, env_count);
	bubble_sort_env(sorted_env, env_count);
	return (sorted_env);
}
