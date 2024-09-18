#include "minishell.h"

int	parse(int ac, char *av[], char *envp[], t_ms *ms)
{
	ms->ac = ac;
	ms->av = av;
	ms->envp = envp;
	ms->paths = extract_paths(envp); // malloc 1
	if (!ms->paths)
		return (0);
	return (1);
}
