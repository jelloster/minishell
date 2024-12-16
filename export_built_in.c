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
	if (setenv_update(key, value, ms->envp) == -1)
		return (-1);
	remove_shell_var(shell_vars, key);
	add_shell_var(shell_vars, key, value); // HERE
	return (0);
}

int	export_built_in(char **args, t_ms *ms, t_shell_var **shell_vars)
{
	int	i;

	printf("Export built in\n");
	if (!args[1])
	{
		print_exported_vars(*shell_vars);
		return (0);
	}
	i = 1;
	while (args[i])
	{
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
