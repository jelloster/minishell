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
	int		fd;
	char	*text;

	if (!args[1])
		return (1);
	fd = STDOUT_FILENO;
	if (args[2] && !ft_strncmp(">", args[2], 1))
	{
		if (!args[3])
			return (1);
		fd = open(args[3], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			return (perror("echo"), 1);
	}
	else if (args[2] && !ft_strncmp(">>", args[2], 2))
	{
		if (!args[3])
			return (1);
		fd = open(args[3], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			return (perror("echo"), 1);
	}
	text = args[1];
	ft_putstr_fd(text, fd);
	write(fd, "\n", 1);
	if (fd != STDOUT_FILENO)
		close(fd);
	return (0);
}

int	setenv_update(const char *key, const char *value, char **envp)
{
	int		i;
	int		env_len;
	size_t	key_len;
	char	*temp;
	char	*new_entry;

	key_len = ft_strlen(key);
	new_entry = ft_strjoin(key, "=");
	if (!new_entry)
		return (-1);
	temp = ft_strjoin(new_entry, value);
	free(new_entry);
	if (!temp)
		return (-1);
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], key, key_len) && envp[i][key_len] == '=')
		{
			free(envp[i]);
			envp[i] = temp;
			return (0);
		}
		i++;
	}
	env_len = strstrlen(envp);
	envp[env_len] = temp;
	envp[env_len + 1] = NULL;
	return (0);
}

