#include "minishell.h"

t_shell_var	*find_shell_var(t_shell_var *shell_vars, const char *key)
{
	while (shell_vars)
	{
		if (!ft_strncmp(shell_vars->key, key, ft_strlen(key) + 1))
			return (shell_vars);
		shell_vars = shell_vars->next;
	}
	return (NULL);
}

int	pwd_built_in(char **msenvp, t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd->args[1] && cmd->args[1][0] == '-')
	{
		write(2, cmd->program_name + 2, ft_strlen(cmd->program_name) - 2);
		write(2, ": pwd: arguments and options aren't supported\n", 46);
		return (0);
	}
	while (msenvp[i])
	{
		if (!ft_strncmp(msenvp[i], "PWD=", 4))
		{
			ft_printf("%s\n", msenvp[i] + 4);
			return (0);
		}
		i++;
	}
	ft_printf("No PWD var found\n");
	return (1);
}

int	env_built_in(char **msenvp, t_cmd *cmd)
{
	int	i;

	if (cmd->args[1])
	{
		write(2, cmd->program_name + 2, ft_strlen(cmd->program_name) - 2);
		write(2, ": env: arguments and options aren't supported\n", 46);
		return (0);
	}
	i = 0;
	while (msenvp[i])
	{
		ft_printf("%s\n", msenvp[i]);
		i++;
	}
	return (0);
}

int	cashmoney_handle(t_ms *ms)
{
	ft_printf("%d", ms->ret_val);
	return (0);
}

int	handle_key_value(char *arg, t_ms *ms, t_shell_var **shell_vars)
{
	char	key[1024];
	char	*value;
	size_t	key_len;
	char	*equal_sign;

	equal_sign = ft_strchr(arg, '=');
	if (!equal_sign)
		return (0);
	key_len = equal_sign - arg;
	if (key_len == 0 || key_len >= sizeof(key))
		return (-1);
	ft_strlcpy(key, arg, key_len + 1);
	value = equal_sign + 1;
	if (setenv_update(key, value, ms->envp) == -1)
		return (-1);
	remove_shell_var(shell_vars, key);
	add_shell_var(shell_vars, key, value);
	return (0);
}

int	export_built_in(char **args, t_ms *ms, t_shell_var **shell_vars)
{
	int	i;

	if (!args[1])
	{
		print_exported_vars(*shell_vars);
		return (0);
	}
	i = 1;
	while (args[i])
	{
		if (ft_strchr(args[i], '='))
		{
			if (handle_key_value(args[i], ms, shell_vars) == -1)
				ft_printf("export: failed to update `%s`\n", args[i]);
		}
		else if (!find_shell_var(*shell_vars, args[i]))
			add_shell_var(shell_vars, args[i], NULL);
		i++;
	}
	return (0);
}
