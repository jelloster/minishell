/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motuomin <motuomin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:46:38 by motuomin          #+#    #+#             */
/*   Updated: 2024/12/16 13:38:20 by motuomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_exported_vars(t_ms *ms, t_shell_var *shell_vars)
{
	char	**sorted_env;

	sorted_env = sort_env(ms->envp);
	if (!sorted_env)
		return ;
	print_env_vars(sorted_env);
	free_array_of_arrays(sorted_env);
	print_shell_vars(shell_vars, ms);
}
