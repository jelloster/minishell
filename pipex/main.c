/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motuomin <motuomin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:48:21 by motuomin          #+#    #+#             */
/*   Updated: 2024/06/18 13:31:53 by motuomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static t_cmd	*init_cmds(int ac, char *av[], char *envp[]);
static t_aae	*init_aae(int ac, char *av[], char *envp[]);
static char		**extract_paths(char *envp[]);

int	main(int ac, char *av[], char *envp[])
{
	t_cmd	*cmds;
	int		i;

	if (ac < 5)
	{
		perror("Incorrect amount of arguments.");
		exit (EXIT_FAILURE);
	}
	cmds = init_cmds(ac, av, envp);
	i = 0;
	while (i + 2 < ac - 1)
	{
		if (extract_command(&cmds[i]) == -1)
			memory_error(cmds, cmds->aae);
		i++;
	}
	return (pipex(cmds, cmds->aae));
}

static t_cmd	*init_cmds(int ac, char *av[], char *envp[])
{
	t_cmd	*cmds;
	t_aae	*aae;
	int		i;

	i = 0;
	aae = init_aae(ac, av, envp);
	if (!aae)
		memory_error(NULL, NULL);
	cmds = malloc((ac - 3) * sizeof(t_cmd));
	if (!cmds)
		memory_error(NULL, aae);
	while (i < ac - 3)
	{
		cmds[i].av_str = av[i + 2];
		cmds[i].pathed_cmd = NULL;
		cmds[i].args = NULL;
		cmds[i].aae = aae;
		i++;
	}
	return (cmds);
}

static t_aae	*init_aae(int ac, char *av[], char *envp[])
{
	char	**paths;
	t_aae	*aae;

	paths = extract_paths(envp);
	aae = malloc(sizeof(t_aae));
	if (!aae)
	{
		free_array_of_arrays(paths);
		return (NULL);
	}
	aae->ac = ac;
	aae->av = av;
	aae->envp = envp;
	aae->paths = paths;
	return (aae);
}

static char	**extract_paths(char *envp[])
{
	char	*path_env;
	char	**paths;
	size_t	i;

	i = 0;
	while (envp[i] != NULL && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (envp[i] == NULL)
		return (NULL);
	path_env = envp[i] + 5;
	paths = ft_split(path_env, ':');
	if (!paths)
		memory_error(NULL, NULL);
	return (paths);
}
