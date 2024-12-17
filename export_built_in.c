/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_built_in.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motuomin <motuomin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 12:24:29 by motuomin          #+#    #+#             */
/*   Updated: 2024/12/16 13:33:11 by motuomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_key_value(char *arg, t_ms *ms, t_shell_var **shell_vars)
{
	char	key[1024];
	char	*value;
	size_t	key_len;
	char	*equal_sign;


	printf("Handle key value\n");
	equal_sign = ft_strchr(arg, '=');
	if (!equal_sign)
		return (0);
	key_len = equal_sign - arg;
	if (key_len == 0 || key_len >= sizeof(key))
		return (-1);
	ft_strlcpy(key, arg, key_len + 1);
	value = equal_sign + 1;
	if (value[0] == '$')
	{
		value = get_env_value(ms, value + 1, ft_strlen(value) - 1);
		if (!value)
			value = "";
	}
	if (setenv_update(key, value, ms->envp) == -1)
		return (-1);
	remove_shell_var(shell_vars, key);
	add_shell_var(shell_vars, key, value); // HERE
	return (0);
}

int	export_built_in(char **args, t_ms *ms, t_shell_var **shell_vars)
{
	int		i;
	char	*key;

	if (!args[1])
	{
		print_exported_vars(ms, *shell_vars);
		return (0);
	}
	i = 1;
	while (args[i])
	{
		key = get_key(args[i]);
		if (!key)
		{
			// add check werhn only KEY
			perror("key malloc");
			return (1);
		}
		else
		{
			if (!key_legit_check(key))
			{
				ft_printf("invalid key shit\n");
				free(key);
				i++;
				continue ;
			}
			else
			{
				ft_printf("good key shit");
				ft_printf("KEY %s\n", key);
				free(key);
			}
		}
		if (ft_strchr(args[i], '='))
		{
			if (handle_key_value(args[i], ms, shell_vars) == -1)
				ft_printf("export: failed to update `%s`\n", args[i]);
		}
		else if (!find_shell_var(*shell_vars, args[i]))
			add_shell_var(shell_vars, args[i], NULL); // HERE too
		i++;
	}
	return (0);
}

int	key_legit_check(char *arg)
{
	int i;

	if (!arg || (!((arg[0] >= 'a' && arg[0] <= 'z')
		|| (arg[0] >= 'A' && arg[0] <= 'Z') || arg[0] == '_')))
		return (0);
	i = 1;
	while (arg[i])
	{
		if (!((arg[i] >= 'a' && arg[i] <= 'z')
			|| (arg[i] >= 'A' && arg[i] <= 'Z')
			|| (arg[i] >= '0' && arg[i] <= '9') || arg[i] == '_'))
			return (0);
		i++;
	}
	return (1);	
}

void	print_env_vars(char **msenvp)
{
	char	*val;
	char	*key;

	while (*msenvp)
	{
		val = ft_strchr(*msenvp, '=');
		if (val)
		{
			key = get_key(*msenvp);
			if (!key)
			{
				perror("malloc");
				return ;
			}
			val++;
			ft_printf("declare -x %s=\"%s\"\n", key, val);
			free(key);
		}
		else
			ft_printf("declare -x %s\n", *msenvp);
		msenvp++;
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
				ft_printf("declare -x %s=\"%s\"\n", current->key, current->value);
			else
				ft_printf("declare -x %s\n", current->key);
		}
		current = current->next;
	}
}

void	print_exported_vars(t_ms *ms, t_shell_var *shell_vars)
{
	print_env_vars(ms->envp);
	print_shell_vars(shell_vars, ms);
}
