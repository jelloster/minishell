#include "minishell.h"

void	add_shell_var(t_shell_var **shell_vars, char *key, char *value)
{
	t_shell_var	*new_var;

	new_var = malloc(sizeof(t_shell_var));
	new_var->key = ft_strdup(key);
	new_var->value = ft_strdup(value);
	new_var->is_exported = 1;
	new_var->next = *shell_vars;
	*shell_vars = new_var;
}

void	remove_shell_var(t_shell_var **shell_vars, char *key)
{
	t_shell_var	*current;
	t_shell_var	*prev;

	current = *shell_vars;
	prev = NULL;
	while (current)
	{
		if (ft_strncmp(current->key, key, ft_strlen(key) + 1) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*shell_vars = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

void	init_shell_vars(char **envp, t_shell_var **shell_vars)
{
	int		i;
	char	*equal_sign;
	char	key[1024];
	char	*value;

	i = 0;
	while (envp[i])
	{
		equal_sign = ft_strchr(envp[i], '=');
		if (equal_sign)
		{
			ft_strlcpy(key, envp[i], equal_sign - envp[i] + 1);
			value = equal_sign + 1;
			add_shell_var(shell_vars, key, value);
		}
		i++;
	}
}

void	print_exported_vars(t_shell_var *shell_vars)
{
	t_shell_var	*current;

	current = shell_vars;
	ft_printf("declare -x variables:\n");
	while (current)
	{
		if (current->value)
			ft_printf("declare -x %s=\"%s\"\n", current->key, current->value);
		else
			ft_printf("declare -x %s\n", current->key);
		current = current->next;
	}
}
