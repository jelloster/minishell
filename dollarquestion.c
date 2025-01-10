/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollarquestion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motuomin <motuomin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:46:38 by motuomin          #+#    #+#             */
/*   Updated: 2025/01/08 22:27:43 by motuomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dollarquestion(t_ms *ms, t_cmd *cmd)
{
	int		i;
	char	*dol_val;

	i = 0;
	while (cmd->args[i])
	{
		if (!ft_strncmp(cmd->args[i], "$?", 3))
		{
			dol_val = ft_itoa(ms->ret_val);
			if (!dol_val)
				exit(free_ms(ms, ms->cmd_line, ms->cmds, 0));
			free(cmd->args[i]);
			cmd->args[i] = ft_strdup(dol_val);
		}
		i++;
	}
}
