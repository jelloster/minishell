/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_functions2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motuomin <motuomin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:07:31 by motuomin          #+#    #+#             */
/*   Updated: 2025/01/13 13:00:12 by motuomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	infile_in_infiles(char **infiles, char *infile)
{
	int	i;

	i = 0;
	if (!infiles | !infile)
		return (0);
	while (infiles[i])
	{
		if (infiles[i] == infile)
			return (1);
		i++;
	}
	return (0);
}

void	free_cmd(t_cmd *cmds, int i)
{
	int	not_free_infile;

	not_free_infile = infile_in_infiles(cmds[i].infiles, cmds[i].infile);
	if (cmds[i].pathed_cmd && cmds[i].pathed_cmd != cmds[i].args[0])
		ft_memdel(&cmds[i].pathed_cmd);
	if (cmds[i].inredirs)
		free(cmds[i].inredirs);
	if (cmds[i].args)
		free_array_of_arrays(cmds[i].args);
	if (cmds[i].infiles)
		free_array_of_arrays(cmds[i].infiles);
	if (cmds[i].infile && !not_free_infile)
		ft_memdel(&cmds[i].infile);
	if (cmds[i].outfile && !cmds[i].outfiles)
		ft_memdel(&cmds[i].outfile);
	if (cmds[i].outfiles)
		free_array_of_arrays(cmds[i].outfiles);
}

void	setup_inredir_arr(t_cmd *cmd)
{
	int		i;
	size_t	len;
	int		i_i;

	i = -1;
	i_i = 0;
	while (cmd->args[++i])
	{
		len = ft_strlen(cmd->args[i]);
		if (is_redirection(cmd->args[i], len)
			&& !is_out_redirection(cmd->args[i], len))
		{
			if (!ft_strncmp("<", cmd->args[i], len))
				cmd->inredirs[i_i++] = INPUT;
			else if (!ft_strncmp("<<", cmd->args[i], len))
				cmd->inredirs[i_i++] = STD_IN;
		}
	}
}
