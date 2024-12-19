#include "minishell.h"

static int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

static void copy_env(char **sorted_env, char **msenvp, int env_count)
{
	int i;

	i = 0;
	while (i < env_count)
	{
		sorted_env[i] = strdup(msenvp[i]);
		if (!sorted_env[i])
		{
			perror("strdup");
			while (--i >= 0)
				free(sorted_env[i]);
			free(sorted_env);
			return ;
		}
		i++;
	}
	sorted_env[env_count] = NULL;
}

static int	count_env(char **msenvp)
{
	int count;

	count = 0;
	while (msenvp[count])
		count++;
	return (count);
}

static char	**sort_env(char **msenvp)
{
	int		i;
	int		j;
	char	*temp;
	char	**sorted_env;
	int		env_count;
	
	env_count = count_env(msenvp);
	sorted_env = malloc(sizeof(char *) * (env_count + 1));
	if (!sorted_env)
		return (NULL);
	copy_env(sorted_env, msenvp, env_count);
	i = 0;
	while (i < env_count - 1)
	{
		j = 0;
		while (j < env_count - i - 1)
		{
			if (ft_strcmp(sorted_env[j], sorted_env[j + 1]) > 0)
			{
				temp = sorted_env[j];
				sorted_env[j] = sorted_env[j + 1];
				sorted_env[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
	return (sorted_env);
}

void	print_exported_vars(t_ms *ms, t_shell_var *shell_vars)
{
	char	**sorted_env;

	sorted_env = sort_env(ms->envp);
	print_env_vars(sorted_env);
	free_array_of_arrays(sorted_env);
	print_shell_vars(shell_vars, ms);
}
