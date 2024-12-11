#include "minishell.h"

static void	exit_built_in(t_cmd *cmd, t_ms *ms);

int	is_built_in(const char *cmd)
{

	return (!ft_strncmp(cmd, "cd", 2)
		|| !ft_strncmp(cmd, "export", 6)
		|| !ft_strncmp(cmd, "unset", 5)
		|| !ft_strncmp(cmd, "echo", 4)
		|| !ft_strncmp(cmd, "$?", 2)
		|| !ft_strncmp(cmd, "pwd", 3)
		|| !ft_strncmp(cmd, "env", 3)
		|| !ft_strncmp(cmd, "exit", 4));
}

int	exe_built_in(t_cmd *cmd, t_ms *ms)
{
	int	ret;

	ret = 1;
	if (!ft_strncmp(cmd->args[0], "cd", 2))
		return (cd_built_in(cmd->args, ms));
	else if (!ft_strncmp(cmd->args[0], "export", 6))
		return (export_built_in(cmd->args, ms, &ms->shell_vars));
	else if (!ft_strncmp(cmd->args[0], "unset", 5))
		ret = unset_built_in(cmd->args, ms);
	else if (!ft_strncmp(cmd->args[0], "echo", 4))
		ret = echo_built_in(cmd, ms, cmd->outfile, cmd->args);
	else if	(!ft_strncmp(cmd->args[0], "pwd", 3))
		ret = pwd_built_in(ms->envp, cmd);
	else if (!ft_strncmp(cmd->args[0], "env", 3))
		ret = env_built_in(ms->envp, cmd);
	else if (!ft_strncmp(cmd->args[0], "$?", 2))
		ret = cashmoney_handle(ms);
	else if (!ft_strncmp(cmd->args[0], "exit", 4))
		exit_built_in(cmd, ms);
	ms->ret_val = ret;
	return (ret);
}

static int	ft_isdigit_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && !(str[i] == '-' && i == 0))
			return (0);
		i++;
	}
	return (1);
}

static void	exit_built_in(t_cmd *cmd, t_ms *ms)
{
	printf("exit\n");
	if (!cmd->args[1])
		exit (free_ms(ms, NULL, ms->cmds, ms->ret_val));
	else
	{
		if (cmd->args[2])
		{
			write(2, ms->program_name + 2, ft_strlen(ms->program_name) - 2);
			write(2, ": exit: too many arguments\n", 27); 
			exit (free_ms(ms, NULL, ms->cmds, 2));
		}
		else if (ft_isdigit_str(cmd->args[1]))
			exit (free_ms(ms, NULL, ms->cmds, ft_atoi(cmd->args[1])));
		else
		{
			write(2, ms->program_name + 2, ft_strlen(ms->program_name) - 2);
			write(2, ": exit: numeric argument required\n", 34);
			exit (free_ms(ms, NULL, ms->cmds, 2));
		}
	}
}
