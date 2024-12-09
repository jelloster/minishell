#include "minishell.h"

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
		ret = pwd_built_in(ms->envp);
	else if (!ft_strncmp(cmd->args[0], "env", 3))
		ret = env_built_in(ms->envp);
	else if (!ft_strncmp(cmd->args[0], "$?", 2))
		ret = cashmoney_handle(ms);
	else if (!ft_strncmp(cmd->args[0], "exit", 4))
		exit (0);
	ms->ret_val = ret;
	return (ret);
}
