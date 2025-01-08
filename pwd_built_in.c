/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_built_in.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motuomin <motuomin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 12:22:22 by motuomin          #+#    #+#             */
/*   Updated: 2025/01/08 15:50:53 by jkarhu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd_built_in(char **msenvp, t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd->args[1] && cmd->args[1][0] == '-')
	{
		write(2, cmd->pn + 2, ft_strlen(cmd->pn) - 2);
		write(2, ": pwd: arguments and options aren't supported\n", 46);
		return (0);
	}
	while (msenvp[i])
	{
		if (!ft_strncmp(msenvp[i], "PWD=", 4))
		{
			ft_printf("%s\n", msenvp[i] + 4);
			return (0);
		}
		i++;
	}
	ft_printf("No PWD var found\n");
	return (1);
}
