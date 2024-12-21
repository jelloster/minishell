#include "minishell.h"

void	free_shell_vars(t_shell_var **shell_vars)
{
	t_shell_var	*current;
	t_shell_var	*temp;

	current = *shell_vars;
	while (current)
	{
		temp = current;
		current = current->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
	*shell_vars = NULL;
}
