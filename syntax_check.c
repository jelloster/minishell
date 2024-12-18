#include "minishell.h"

int	syntax_check(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		if (!ft_strncmp(split[i], "|", 2) && !ft_strncmp(split[i + 1], "|", 2))
			return (0);
		if (!ft_strncmp(split[i], "|", 2) && !split[i + 1])
			return (0);
		if (!ft_strncmp(split[i], ">", 2) && !split[i + 1])
			return (0);
		if (!ft_strncmp(split[i], "<", 2) && !split[i + 1])
			return (0);
		if (!ft_strncmp(split[i], ">>", 3) && !split[i + 1])
			return (0);
		if (!ft_strncmp(split[i], "<<", 3) && !split[i + 1])
			return (0);
		i++;
	}
	return (1);
}
