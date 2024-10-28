#include "minishell.h"

static int		cmd_count_words(char const *s);
static void		*cmd_free_memory(char **res, char **r_s);
static char	*arg_cpy(char **res, char const **s, char **r_s);

char	**cmd_split(char const *s)
{
	char	**res;
	char	**res_start;
	int	count;

	count = cmd_count_words(s);
	if (count == -1)
		return (NULL);
	res = malloc((count + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	res_start = res;
	while (*s)
	{
		while (*s == ' ')
			s++;
		if (*s)
			arg_cpy(res, &s, res_start);
		if (!*res)
			return (NULL);
		res++;
	}
	*res = NULL;
	return (res_start);
}

static char	*arg_cpy(char **res, char const **s, char **r_s)
{
	char	*arg;
	int	len;

	len = arg_strlen((char *)*s);
	arg = malloc(sizeof(char) * (len + 1));
	if (!arg)
		return (cmd_free_memory(res, r_s));
	arg_strcpy(*s, arg);
	*s += arg_total_strlen((char *)*s);
	*res = arg;
	return (arg);
}



static int	cmd_count_words(char const *s)
{
	int		i;
	int		count;
	char	quote;

	i = 0;
	count = 1;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			if (i > 0)
				count++;
			quote = s[i];
			i++;
			while (s[i] != quote && s[i])
				i++;
			if (!s[i])
				return (-1);
		}
		else if (i > 0 && s[i] != ' ' && s[i - 1] == ' ')
			count++;
		if (s[i])
			i++;
	}
	return (count);
}

static void	*cmd_free_memory(char **res, char **res_start)
{
	while (res > res_start)
		free(*(--res));
	free(res_start);
	return (NULL);
}
