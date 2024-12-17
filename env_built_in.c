/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_built_in.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motuomin <motuomin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 12:23:06 by motuomin          #+#    #+#             */
/*   Updated: 2024/12/16 12:24:14 by motuomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_built_in(char **msenvp, t_cmd *cmd)
{
	int	i;

	if (cmd->args[1])
	{
		write(2, cmd->program_name + 2, ft_strlen(cmd->program_name) - 2);
		write(2, ": env: arguments and options aren't supported\n", 46);
		return (0);
	}
	i = 0;
	while (msenvp[i])
	{
		ft_printf("%s\n", msenvp[i]);
		i++;
	}
	return (0);
}
