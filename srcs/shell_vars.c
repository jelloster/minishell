/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_vars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motuomin <motuomin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 12:17:05 by motuomin          #+#    #+#             */
/*   Updated: 2025/01/09 00:13:50 by motuomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	add_shell_var(t_shell_var **shell_vars, char *key, char *value)
{
	t_shell_var	*new_var;

	new_var = malloc(sizeof(t_shell_var));
	if (!new_var)
		return (0);
	new_var->key = ft_strdup(key);
	new_var->value = ft_strdup(value);
	new_var->is_exported = 1;
	new_var->next = *shell_vars;
	*shell_vars = new_var;
	return (1);
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
	int		i;
	int		key_len;

	val = ft_strchr(envp, '=');
	if (val)
		key_len = val - envp;
	else
		key_len = ft_strlen(envp);
	key = malloc(key_len + 1);
	if (!key)
		return (NULL);
	i = 0;
	while (i < key_len)
	{
		key[i] = envp[i];
		i++;
	}
	key[i] = '\0';
	return (key);
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
