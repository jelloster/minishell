/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motuomin <motuomin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:46:38 by motuomin          #+#    #+#             */
/*   Updated: 2025/01/13 13:57:34 by motuomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expanded_str(char *arg, char *value, int dollar_pos);
static int	c_n_r(t_cmd *cmd, int j, int y, t_ms *ms);

int	expand_args(t_cmd *cmd, t_ms *ms)
{
	int	j;
	int	y;

	j = -1;
	while (cmd->args[++j])
	{
		y = -1;
		while (cmd->args[j][++y])
		{
			if (cmd->args[j][y] == '$')
			{
				y++;
				if (!c_n_r(cmd, j, y, ms))
					return (0);
			}
		}
	}
	return (1);
}

static int	c_n_r(t_cmd *cmd, int j, int y, t_ms *ms)
{
	char	*value;
	char	*temp;

	value = get_env_value(ms, &cmd->args[j][y], \
		strlen_mod(&cmd->args[j][y], ' '));
	if (value)
	{
		temp = cmd->args[j];
		cmd->args[j] = expanded_str(cmd->args[j], value, y - 1);
		if (!cmd->args[j])
			return (0);
		free(temp);
	}
	return (1);
}

static char	*expanded_str(char *arg, char *value, int dollar_pos)
{
	char	*result;
	char	*prefix;
	char	*suffix;
	char	*dollar;

	dollar = arg + dollar_pos;
	prefix = ft_substr(arg, 0, dollar - arg);
	if (!prefix)
		return (NULL);
	suffix = ft_strdup(dollar + strlen_mod(dollar, ' '));
	if (!suffix)
		return (free(prefix), NULL);
	result = ft_strjoin(prefix, value);
	if (!result)
	{
		free(prefix);
		free(suffix);
		return (NULL);
	}
	free(prefix);
	prefix = result;
	result = ft_strjoin(result, suffix);
	free(prefix);
	free(suffix);
	return (result);
}
