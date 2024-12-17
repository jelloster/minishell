/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motuomin <motuomin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:53:22 by motuomin          #+#    #+#             */
/*   Updated: 2024/12/16 12:27:32 by motuomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	dollar_value_print(t_ms *ms, char *arg, int fd)
{
	int		i;
	char	*output;

	i = 0;
	if (arg[1] == '?')
	{
		ft_printf("%d", ms->ret_val);
		return (2); // why 2?
	}
	while (arg[i] && arg[i] != ' ')
		i++;
	output = get_env_value(ms, arg + 1, i - 1);
	if (output)
		ft_putstr_fd(output, fd);
	return (i);
}

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

static void	handle_squiggly(char **args, int *i, int *j, int fd, t_ms *ms)
{
	char *home;

	if (args[*i][*j] == '~' && (args[*i][*j - 1] == ' ' || *j == 0))
	{
		home = get_env_value(ms, "HOME", 4);
		ft_putstr_fd(home, fd);
		(*j)++;
	}
}

static void	iterate_args(char **args, int fd, t_ms *ms)
{
	int		i;
	int		j;

	i = 1;
	if (args[1] && !ft_strncmp(args[1], "-n", 3))
		i++;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (args[i][j] == '$')
				j += dollar_value_print(ms, &args[i][j], fd);
			else
			{
				if (args[i][j] == '\xFF')
					args[i][j] = '$';
				handle_squiggly(args, &i, &j, fd, ms);
				write(fd, &args[i][j], 1);
				if (args[i][j] && args[i][j + 1])
					j++;
			}
		}
		if (args[i + 1] && ft_strlen(args[i]) != 0)
			ft_putstr_fd(" ", fd);
		i++;
	}
}

int	echo_built_in(t_cmd *cmd, t_ms *ms, char **args)
{
	int		fd;

	signal_check(ms);
	if (!handle_io(&fd, cmd))
		return (1);
	iterate_args(args, fd, ms);
	if (!(cmd->args[1] && !ft_strncmp(cmd->args[1], "-n", 3)))
		write(fd, "\n", 1);
	if (fd != STDOUT_FILENO)
		close(fd);
	return (0);
}

