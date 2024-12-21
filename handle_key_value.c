#include "minishell.h"

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
	if (value[0] == '$')
	{
		value = get_env_value(ms, value + 1, ft_strlen(value) - 1);
		if (!value)
			value = "";
	}
	if (setenv_update(key, value, ms) == -1)
		return (-1);
	remove_shell_var(shell_vars, key);
	add_shell_var(shell_vars, key, value);
	return (0);
}
