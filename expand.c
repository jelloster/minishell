/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motuomin <motuomin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:46:38 by motuomin          #+#    #+#             */
/*   Updated: 2025/01/15 17:55:32 by motuomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expanded_str(char *arg, char *value, int dollar_pos);
static int	c_n_r(t_cmd *cmd, int j, int y, t_ms *ms);
static char	*no_value(char *arg, int dollar_pos);

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
				y = -1;
			}
		}
	}
	return (1);
}

static int	c_n_r(t_cmd *cmd, int j, int y, t_ms *ms)
{
	char	*value;
	char	*temp;
	int		len;

	len = strlen_specialchar(&cmd->args[j][y]);
	temp = cmd->args[j];
	value = get_env_value(ms, &cmd->args[j][y], len);
	if (value)
		cmd->args[j] = expanded_str(cmd->args[j], value, y - 1);
	else if (cmd->args[j][y] == '?'
		&& !ft_strncmp(&cmd->args[j][y - 1], "$?", len + 1))
	{
		value = ft_itoa(ms->ret_val);
		if (!value)
			return (0);
		cmd->args[j] = expanded_str(cmd->args[j], value, y - 1);
		free(value);
	}
	else
		cmd->args[j] = no_value(cmd->args[j], y - 1);
	if (!cmd->args[j])
		return (0);
	free(temp);
	return (1);
}

static char	*no_value(char *arg, int dollar_pos)
{
	char	*result;
	char	*prefix;
	char	*suffix;
	char	*dollar;

	dollar = arg + dollar_pos;
	prefix = ft_substr(arg, 0, dollar - arg);
	if (!prefix)
		return (NULL);
	suffix = ft_strdup(dollar + strlen_specialchar(dollar + 1) + 1);
	if (!suffix)
		return (free(prefix), NULL);
	result = ft_strjoin(prefix, suffix);
	free(prefix);
	free(suffix);
	return (result);
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
	if (*(dollar + 1) == '?')
		suffix = ft_strdup(dollar + 2);
	else
		suffix = ft_strdup(dollar + strlen_specialchar(dollar + 1) + 1);
	if (!suffix)
		return (free(prefix), NULL);
	result = ft_strjoin(prefix, value);
	free(prefix);
	if (!result)
		return (free(suffix), NULL);
	prefix = result;
	result = ft_strjoin(result, suffix);
	free(prefix);
	free(suffix);
	return (result);
}
