/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motuomin <motuomin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:47:12 by motuomin          #+#    #+#             */
/*   Updated: 2024/10/10 16:06:50 by motuomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	free_n_exit(char *p_cmd, char *s_cmd, char **args, int ret);

int	extract_command(t_cmd *cmd)
{
	char	*no_path_cmd;

	cmd -> args = awk_split((char const *)cmd->av_str);
	if (cmd -> args == NULL)
		return (-1);
	if (cmd -> args[0] && access(cmd->args[0], X_OK) == 0)
	{
		cmd->pathed_cmd = cmd->args[0];
		no_path_cmd = cmd->args[0] + strlen_mod(cmd->args[0], '/');
		cmd->args[0] = no_path_cmd;
	}
	else
		return (extract_pathed_cmd(cmd, cmd->aae->paths));
	return (1);
}
static int	free_n_exit(char *p_cmd, char *s_cmd, char **args, int ret)
{
	size_t	i;

	i = 0;
	if (p_cmd)
		free(p_cmd);
	if (s_cmd)
		free(s_cmd);
	if (args)
	{
		while (args[i])
			free(args[i++]);
		free(args);
	}
	return (ret);
}

/*
int	exe_cmd(t_cmd cmd)
{
	if (cmd.pathed_cmd == NULL || access(cmd.pathed_cmd, F_OK) == -1)
	{
//		error_msg(COMMAND_NOT_FOUND, cmd.args[0], cmd.aae->av[0]);
		exit(127);
	}
	if (access(cmd.pathed_cmd, X_OK) == 0)
		execve(cmd.pathed_cmd, cmd.args, cmd.envp);
	else
		exit(126);
	exit(2);
}
*/
