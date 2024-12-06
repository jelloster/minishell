#include "minishell.h"

int	cd_built_in(char **args, t_ms *ms)
{
	char	cwd[1024];
	char	*home;
	
	if (!args[1])
	{
		home = getenv("HOME");
		if (!home)
		{
			perror("HOME env");
			return (1);
		}
		if (chdir(home) == -1)
		{
			perror("cd");
			return (1);
		}
	}
	else
	{
		if (chdir(args[1]) == -1)
		{
			perror("cd");
			return (1);
		}
	}
	if (getcwd(cwd, sizeof(cwd)))
		setenv_update("PWD", cwd, ms->envp);
	return (0);
}

int	unsetenv_manual(const char *key, char **envp)
{
	int		i;
	size_t	key_len;

	i = 0;
	key_len = ft_strlen(key);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, key_len) == 0 && envp[i][key_len] == '=')
		{
			while (envp[i + 1])
			{
				envp[i] = envp[i + 1];
				i++;
			}
			envp[i] = NULL;
			return (0);
		}
		i++;
	}
	return (0);
}

int	unset_built_in(char **args, t_ms *ms)
{
	int	i;

	if (!args[1])
	{
		perror("unser");
		return (1);
	}
	i = 1;
	while (args[i])
	{
		unsetenv_manual(args[i], ms->envp);
		i++;
	}
	return (0);
}

int	echo_built_in(char **args)
{
	int	newline;
	int	i;

	newline = 1;
	i = 1;
	if (args[1] && ft_strncmp(args[1], "-n", 2) == 0)
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		write(1, args[i], ft_strlen(args[i]));
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (newline)
		write(1, "\n", 1);
	return (0);
}

int setenv_update(const char *key, const char *value, char **envp)
{
    size_t key_len = ft_strlen(key);
    char *new_entry = ft_strjoin(key, "=");
    if (!new_entry)
        return -1;

    char *temp = ft_strjoin(new_entry, value);
    free(new_entry);
    if (!temp)
        return -1;

    for (int i = 0; envp[i]; i++)
    {
        if (!ft_strncmp(envp[i], key, key_len) && envp[i][key_len] == '=')
        {
            free(envp[i]);
            envp[i] = temp;
            return 0;
        }
    }

    // Add new variable to envp
    int env_len = strstrlen(envp);
    envp[env_len] = temp;
    envp[env_len + 1] = NULL;

    return 0;
}

