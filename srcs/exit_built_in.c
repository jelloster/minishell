/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motuomin <motuomin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 13:01:56 by motuomin          #+#    #+#             */
/*   Updated: 2025/01/13 17:51:59 by motuomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	ft_isdigit_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && !(str[i] == '-' && i == 0))
			return (0);
		i++;
	}
	return (1);
}

void	exit_built_in(t_cmd *cmd, t_ms *ms)
{
	ft_printf("exit\n");
	if (!cmd->args[1])
		exit (free_ms(ms, NULL, ms->cmds, ms->ret_val));
	else
	{
		if (cmd->args[2])
		{
			write(2, ms->program_name + 2, ft_strlen(ms->program_name) - 2);
			write(2, ": exit: too many arguments\n", 27);
		}
		else if (ft_isdigit_str(cmd->args[1]) && ft_strlen(cmd->args[1]) < 20)
			exit (free_ms(ms, NULL, ms->cmds, ft_atoi(cmd->args[1])));
		else
		{
			write(2, ms->program_name + 2, ft_strlen(ms->program_name) - 2);
			write(2, ": exit: numeric argument required\n", 34);
			exit (free_ms(ms, NULL, ms->cmds, 2));
		}
	}
}
