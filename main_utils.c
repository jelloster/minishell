/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motuomin <motuomin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:06:18 by motuomin          #+#    #+#             */
/*   Updated: 2025/01/13 19:18:00 by motuomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_sigint_heredoc(t_cmd *cmds, t_ms *ms)
{
	int	i;

	i = 0;
	if (ms->dont)
	{
		while (i < ms->cmd_n)
		{
			if (cmds[i].inredir == STD_IN && cmds[i].infile)
				unlink(cmds[i].infile);
			i++;
		}
		exit(free_ms(ms, ms->cmd_line, cmds, 130));
	}
}
