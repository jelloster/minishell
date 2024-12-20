#include "minishell.h"

void	print_exported_vars(t_ms *ms, t_shell_var *shell_vars)
{
	char	**sorted_env;

	sorted_env = sort_env(ms->envp);
	if (!sorted_env)
		return ;
	print_env_vars(sorted_env);
	free_array_of_arrays(sorted_env);
	print_shell_vars(shell_vars, ms);
}
