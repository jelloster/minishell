/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_vars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motuomin <motuomin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 12:17:05 by motuomin          #+#    #+#             */
/*   Updated: 2024/12/16 13:37:50 by motuomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_shell_var(t_shell_var **shell_vars, char *key, char *value)
{
	t_shell_var	*new_var;

	new_var = malloc(sizeof(t_shell_var));
	new_var->key = ft_strdup(key);
	new_var->value = ft_strdup(value);
	new_var->is_exported = 1;
	new_var->next = *shell_vars;
	*shell_vars = new_var;
}

void	remove_shell_var(t_shell_var **shell_vars, char *key)
{
	t_shell_var	*current;
	t_shell_var	*prev;

	current = *shell_vars;
	prev = NULL;
	while (current)
	{
		if (ft_strncmp(current->key, key, ft_strlen(key) + 1) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*shell_vars = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

t_shell_var	*find_shell_var(t_shell_var *shell_vars, const char *key)
{
	while (shell_vars)
	{
		if (!ft_strncmp(shell_vars->key, key, ft_strlen(key) + 1))
			return (shell_vars);
		shell_vars = shell_vars->next;
	}
	return (NULL);
}

char	*get_key(char *envp)
{
	char	*val;
	char	*key;
	int		key_len;
	int		i;

	val = ft_strchr(envp, '=');
	if (val)
	{
		key_len = val - envp;
		key = malloc(key_len + 1);
		if (!key)
			return (NULL);
		ft_strlcpy(key, envp, key_len + 1);
		return (key);
	}
	else
	{
		i = 0;
		key = malloc(ft_strlen(envp) + 1);
		while (envp[i])
		{
			key[i] = envp[i];
			i++;
		}
		key[i] = '\0';
		return (key);
	}
}

void	print_shell_vars(t_shell_var *shell_vars, t_ms *ms)
{
	t_shell_var	*current;

	current = shell_vars;
	while (current)
	{
		if (!get_env_value(ms, current->key, 0))
		{
			if (current->value)
				ft_printf("declare -x %s=\"%s\"\n",
					current->key, current->value);
			else
				ft_printf("declare -x %s\n", current->key);
		}
		current = current->next;
	}
}
