/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motuomin <motuomin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 12:30:48 by motuomin          #+#    #+#             */
/*   Updated: 2025/01/08 14:40:15 by jkarhu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_built_in(const char *cmd)
{
	return (!ft_strncmp(cmd, "cd", 3)
		|| !ft_strncmp(cmd, "export", 7)
		|| !ft_strncmp(cmd, "unset", 6)
		|| !ft_strncmp(cmd, "echo", 5)
		|| !ft_strncmp(cmd, "$?", 3)
		|| !ft_strncmp(cmd, "pwd", 4)
		|| !ft_strncmp(cmd, "env", 4)
		|| !ft_strncmp(cmd, "exit", 5));
}

int	exe_built_in(t_cmd *cmd, t_ms *ms)
{
	int	ret;

	ret = 1;
	if (!ft_strncmp(cmd->args[0], "cd", 3))
		return (cd_built_in(cmd->args, ms));
	else if (!ft_strncmp(cmd->args[0], "export", 6))
		return (export_built_in(cmd->args, ms, &ms->shell_vars));
	else if (!ft_strncmp(cmd->args[0], "unset", 5))
		ret = unset_built_in(cmd->args, ms);
	else if (!ft_strncmp(cmd->args[0], "echo", 4))
		ret = echo_built_in(cmd, ms, cmd->args);
	else if (!ft_strncmp(cmd->args[0], "pwd", 3))
		ret = pwd_built_in(ms->envp, cmd);
	else if (!ft_strncmp(cmd->args[0], "env", 3))
		ret = env_built_in(ms->envp, cmd);
	else if (!ft_strncmp(cmd->args[0], "exit", 4))
	{
		update_shlvl(ms, -1);
		exit_built_in(cmd, ms);
	}
	ms->ret_val = ret;
	return (ret);
}
