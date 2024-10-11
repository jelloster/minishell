#include "minishell.h"

char	**extract_paths(char *envp[])
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
	paths = ft_split(path_env, ':'); // malloc
	if (!paths)
		return (NULL);
	return (paths);
}
