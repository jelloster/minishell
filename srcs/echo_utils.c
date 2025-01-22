/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motuomin <motuomin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:53:22 by motuomin          #+#    #+#             */
/*   Updated: 2024/12/16 12:27:32 by motuomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	handle_squiggly(char *arg, int *j, int fd, t_ms *ms)
{
	char	*home;

	if (arg[*j] == '~' && (*j == 0 || arg[*j - 1] == ' '))
	{
		home = get_env_value(ms, "HOME", 4);
		ft_putstr_fd(home, fd);
		(*j)++;
	}
}

int	handle_flag(char **args)
{
	int	i;

	i = 1;
	while (args[i] && !ft_strncmp(args[i], "-n", 2))
		i++;
	return (i);
}
