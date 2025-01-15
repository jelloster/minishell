/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motuomin <motuomin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:53:22 by motuomin          #+#    #+#             */
/*   Updated: 2025/01/11 17:16:21 by motuomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_io(int *fd, t_cmd *cmd)
{
	*fd = STDOUT_FILENO;
	if (cmd->outredir == REPLACE && cmd -> outfile)
	{
		*fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (*fd == -1)
			return (perror("echo"), 0);
	}
	else if (cmd->outredir == ADD)
	{
		*fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (*fd == -1)
			return (perror("echo"), 0);
	}
	return (1);
}

static void	iterate_args(char **args, int fd, t_ms *ms)
{
	int		i;
	int		j;

	i = handle_flag(args);
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (args[i][j] == '\xFF')
				args[i][j] = '$';
			handle_squiggly(args[i], &j, fd, ms);
			write(fd, &args[i][j], 1);
			if (args[i][j])
				j++;
		}
		if (args[i + 1] && ft_strlen(args[i]) != 0)
			ft_putstr_fd(" ", fd);
		i++;
	}
}

int	echo_built_in(t_cmd *cmd, t_ms *ms, char **args)
{
	int	fd;

	if (!handle_io(&fd, cmd))
		return (1);
	iterate_args(args, fd, ms);
	if (!(cmd->args[1] && !ft_strncmp(cmd->args[1], "-n", 2)))
		write(fd, "\n", 1);
	if (fd != STDOUT_FILENO)
		close(fd);
	return (0);
}
