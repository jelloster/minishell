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

int	echo_built_in(t_cmd *cmd, t_ms *ms,  char *file, char **args)
{
	int		fd;
	int		i;

		
	fd = STDOUT_FILENO;
	dollar_check(ms, args);
	if (cmd->outredir == REPLACE && cmd -> outfile)
	{
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			return (perror("echo"), 1);
	}
	else if (cmd->outredir == ADD)
	{
		fd = open(file , O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			return (perror("echo"), 1);
	}
	i = 1;
	while (args[i])
	{	
		ft_putstr_fd(args[i], fd);
		if (args[i + 1])
			ft_putstr_fd(" ", fd);
		i++;
	}
	write(fd, "\n", 1);
	if (fd != STDOUT_FILENO)
		close(fd);
	return (0);
}

void	dollar_check(t_ms *ms, char **args)
{
	int		i;
	int		j;
	int		found_key;
	char	*temp;

	i = 0;
	j = 0;
	while (args[i])
	{
		found_key = 0;
		if (args[i][0] == '$')
		{
			if (args[i][1] == '?')
			{
				cashmoney_handle(ms);
				temp = ft_strdup(args[i] + 2);
				if (!temp)
				{
					// free stuff if malloc
					return ;
				}
				free (args[i]);
				args[i] = temp;
				break ;

			}
			while (ms->envp[j])
			{
				if (!ft_strncmp((args[i] + 1), ms->envp[j], ft_strlen(args[i]) - 1))
				{
					temp = ft_strdup(ms->envp[j] + ft_strlen(args[i]));
					free(args[i]);
					args[i] = temp;
					found_key = 1;
				}
				j++;
			}
			if (!found_key)
			{
				free(args[i]);
				args[i] = NULL;
			}
		}
		i++;
	}
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

