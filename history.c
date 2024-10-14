#include "minishell.h"

int	update_history(t_ms *ms, char *cmd_line)
{
	char	**new_history;
	int	i;

	i = 0;
	ms->his_n++;
	new_history = malloc((ms->his_n + 1) * sizeof(char *)); // malloc 
	if (!new_history)
		return (0);
	while (i < ms->his_n - 1)
	{
		new_history[i] = ms->history[i];
		i++;
	}
	new_history[i] = cmd_line;
	new_history[ms->his_n] = NULL;
	if (ms->history)
		free(ms->history);
	ms->history = new_history;
	return (1);
}
