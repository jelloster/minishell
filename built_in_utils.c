#include "minishell.h"

int	is_built_in(const char *cmd)
{

	return (!ft_strncmp(cmd, "cd", 2)
		|| !ft_strncmp(cmd, "export", 6)
		|| !ft_strncmp(cmd, "unset", 5)
		|| !ft_strncmp(cmd, "echo", 4));
}

int	exe_built_in(t_cmd *cmd, t_ms *ms)
{
	if (!ft_strncmp(cmd->args[0], "cd", 2))
		return (cd_built_in(cmd->args, ms));
/*	else if (!ft_strncmp(cmd->args[0], "export"))
		return (export(cmd->args));*/
	else if (!ft_strncmp(cmd->args[0], "unset", 5))
		return (unset_built_in(cmd->args, ms));
	else if (!ft_strncmp(cmd->args[0], "echo", 4))
		return (echo_built_in(cmd->args));
	return (1);
}
