/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motuomin <motuomin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 12:04:03 by motuomin          #+#    #+#             */
/*   Updated: 2024/12/16 14:08:16 by motuomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_inredirs(t_cmd *cmd)
{
	int	count;
	int	i;
	int	len;

	count = 0;
	i = 0;
	while (cmd->args[i])
	{
		len = ft_strlen(cmd->args[i]);
		if (!ft_strncmp("<", cmd->args[i], len)
			|| !ft_strncmp("<<", cmd->args[i], len))
			count++;
		i++;
	}
	return (count);
}

/*
 * Function : check_for_redirections
 *
 * Returns 1 if there is a redirection symbol in the args of the given cmd and
 * 0 otherwise.
*/

int	check_for_redirections(t_cmd *cmd)
{
	if (str_in_array_of_strs(">", cmd->args))
		return (1);
	else if (str_in_array_of_strs("<", cmd->args))
		return (1);
	else if (str_in_array_of_strs(">>", cmd->args))
		return (1);
	else if (str_in_array_of_strs("<<", cmd->args))
		return (1);
	return (0);
}

/*
 * Function : is_out_redirection
 *
 * Returns 1 if the given string (str) is ">" or ">>", otherwise a 0.
*/

int	is_out_redirection(char *str, size_t len)
{
	if (!ft_strncmp(">", str, len) || !ft_strncmp(">>", str, len))
		return (1);
	return (0);
}

static int	count_outredirs(t_cmd *cmd)
{
	int	count;
	int	i;
	int	len;

	count = 0;
	i = 0;
	while (cmd->args[i])
	{
		len = ft_strlen(cmd->args[i]);
		if (!ft_strncmp(">", cmd->args[i], len)
			|| !ft_strncmp(">>", cmd->args[i], len))
			count++;
		i++;
	}
	return (count);
}

int	malloc_for_redirs(t_cmd *cmd)
{
	int	i;

	i = -1;
	cmd->infile_n = count_inredirs(cmd);
	cmd->infiles = malloc((cmd->infile_n + 1) * sizeof(char *));
	if (!cmd->infiles)
		return (-1);
	while (++i <= cmd->infile_n)
		cmd->infiles[i] = NULL;
	cmd->outfile_n = count_outredirs(cmd);
	cmd->outfiles = malloc((cmd->outfile_n + 1) * sizeof(char *));
	if (!cmd->outfiles)
	{
		free_array_of_arrays(cmd->infiles);
		cmd->infiles = NULL;
		return (-1);
	}
	cmd->outfiles[cmd->outfile_n] = NULL;
	return (1);
}
