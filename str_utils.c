#include "minishell.h"

int	free_array_of_arrays(char **arr)
{
	size_t	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
		{
			if (arr[i])
			{
				free(arr[i]);
				arr[i] = NULL;
			}
			i++;
		}
		free(arr);
		arr = NULL;
	}
	return (-1);
}

size_t	strlen_mod(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] != c && s[i] != '\0')
		i++;
	return (i);
}

int	str_in_array_of_strs(void *str, void **strs)
{
	int	i;
	int	len;

	i = 0;
	while (strs[i])
	{
		len = ft_strlen(strs[i]);
		if (ft_stlen(str) > len)
			len = ft_strlen(str);
		if (ft_strncmp(str, strs[i], len) == 0)
			return (1);
	}
	return (0);
}
