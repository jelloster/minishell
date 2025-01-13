/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_built_in.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motuomin <motuomin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 12:24:29 by motuomin          #+#    #+#             */
/*   Updated: 2025/01/13 13:06:58 by motuomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_export_key(char *arg, char **key)
{
	if (arg[0] == '\0')
	{
		ft_printf("export: not a valid identifier\n");
		return (1);
	}
	*key = get_key(arg);
	if (!(*key))
	{
		ft_printf("export: failed to retrieve key\n");
		return (1);
	}
	if (!key_legit_check(*key))
	{
		ft_printf("export: not a valid identifier\n");
		return (1);
	}
	return (0);
}

static int	process_export(char *arg, t_ms *ms, t_shell_var **shell_vars)
{
	char	*key;

	if (handle_export_key(arg, &key))
	{
		if (key)
			free(key);
		return (1);
	}
	if (ft_strchr(arg, '='))
	{
		if (handle_key_value(arg, ms, shell_vars) == -1)
			ft_printf("export: failed to update `%s`\n", arg);
	}
	else if (!find_shell_var(*shell_vars, arg))
	{
		if (!add_shell_var(shell_vars, arg, ""))
			return (1);
	}
	free(key);
	return (0);
}

int	export_built_in(char **args, t_ms *ms, t_shell_var **shell_vars)
{
	int	i;

	if (!args[1])
	{
		print_exported_vars(ms, *shell_vars);
		return (0);
	}
	if (args[1][0] == '-')
	{
		ft_printf("export: flags are not supported in minishell\n");
		return (1);
	}
	i = 1;
	while (args[i])
	{
		if (process_export(args[i], ms, shell_vars))
			return (1);
		i++;
	}
	return (0);
}

int	key_legit_check(char *arg)
{
	int	i;

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
