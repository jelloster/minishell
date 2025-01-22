/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motuomin <motuomin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 12:04:03 by motuomin          #+#    #+#             */
/*   Updated: 2025/01/18 16:42:49 by motuomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	assign_redirection_type(t_ms *ms, t_cmd *cmd, int len, int i);
static int	parse_redir_args(t_cmd *cmd, char **paths, int redirs);

int	handle_redirected_cmd(t_ms *ms, t_cmd *cmd, char **paths)
{
	int	i;
	int	len;

	i = 0;
	if (malloc_for_redirs(cmd) == -1)
		return (0);
	cmd->o_i = 0;
	cmd->i_i = 0;
	while (cmd->args[i])
	{
		len = ft_strlen(cmd->args[i]);
		if (is_redirection(cmd->args[i], len))
			if (!assign_redirection_type(ms, cmd, len, i))
				return (0);
		i++;
	}
	return (parse_redir_args(cmd, paths, cmd->infile_n + cmd->outfile_n));
}

/*
 * Checks that :
 * - the redirection symbol is not the last string in the args
 * - there are no 2 redirection symbols after each other
 * - there is only 1 redirection for output and input
 */
static int	assign_redirection_type(t_ms *ms, t_cmd *cmd, int len, int i)
{
	int	temp;

	if (!ft_strncmp(">", cmd->args[i], len)
		&& cmd->args[i + 1] && !is_redirection(cmd->args[i + 1], len))
		cmd->outredir = REPLACE;
	else if (!ft_strncmp("<", cmd->args[i], len)
		&& cmd->args[i + 1] && !is_redirection(cmd->args[i + 1], len))
		cmd->inredir = INPUT;
	else if (!ft_strncmp(">>", cmd->args[i], len)
		&& cmd->args[i + 1] && !is_redirection(cmd->args[i + 1], len))
		cmd->outredir = ADD;
	else if (!ft_strncmp("<<", cmd->args[i], len)
		&& cmd->args[i + 1] && !is_redirection(cmd->args[i + 1], len))
	{
		cmd->inredir = STD_IN;
		temp = heredoc_write(cmd->args[i + 1], ms, cmd);
		if (!temp)
			return (0);
		if (temp == 130)
			ms->ret_val = 130;
	}
	else
		return (0);
	return (1);
}

static void	parse_redir_args_2(t_cmd *cmd, char **new_args, int *i, int *n_i)
{
	int	len;

	while (cmd->args[*i])
	{
		len = ft_strlen(cmd->args[*i]);
		if (is_redirection(cmd->args[*i], len))
		{
			if (is_out_redirection(cmd->args[*i], len))
			{
				cmd->outfiles[cmd->o_i++] = cmd->args[++(*i)];
				cmd->outfile = cmd->args[*i];
			}
			else if (cmd->inredir != STD_IN)
				here_doc_file_thing(cmd, i);
			else
				free(cmd->args[++(*i)]);
			free (cmd->args[*i - 1]);
			(*i)++;
		}
		else
			new_args[(*n_i)++] = cmd->args[(*i)++];
	}
}

static int	parse_redir_args(t_cmd *cmd, char **paths, int redirs)
{
	char	**new_args;
	int		n_i;
	int		i;

	i = 0;
	n_i = 0;
	new_args = malloc((strstrlen(cmd->args) - redirs * 2 + 1) * sizeof(char *));
	if (!new_args)
		return (0);
	setup_inredir_arr(cmd);
	parse_redir_args_2(cmd, new_args, &i, &n_i);
	new_args[n_i] = NULL;
	free(cmd->args);
	cmd->args = new_args;
	return (extract_pathed_cmd(cmd, paths));
}

/*
 * Function : is_redirection
 *
 * Returns 1 if the given string (str) of size (len) is a redirection symbol
 * and 0 if it isn't.
*/
int	is_redirection(char *str, size_t len)
{
	if (!ft_strncmp(">", str, len))
		return (1);
	else if (!ft_strncmp("<", str, len))
		return (1);
	else if (!ft_strncmp(">>", str, len))
		return (1);
	else if (!ft_strncmp("<<", str, len))
		return (1);
	return (0);
}
