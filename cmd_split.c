#include "minishell.h"

static int		cmd_count_words(char const *s);
static void		*cmd_free_memory(char **res, char **r_s);
static char		**normal_args(char **arg, char const **s, char **r_s);
static char		**quoted_args(char **res, char const **s, char **r_s, char c);

char	**cmd_split(char const *s)
{
	char	**res;
	char	**res_start;

	res = malloc((cmd_count_words(s) + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	res_start = res;
	while (*s)
	{
		while (*s == ' ')
			s++;
		if (*s == '\'' || *s == '\"')
			res = quoted_args(res, &s, res_start, *s);
		if (*s != ' ' && *s != '\0')
			res = normal_args(res, &s, res_start);
		if (!res)
			return (NULL);
	}
	*res = NULL;
	return (res_start);
}

static char	**quoted_args(char **res, char const **s, char **r_s, char c)
{
	char	*split;

	(*s)++;
	split = malloc(sizeof(char) * (strlen_mod(*s, c) + 1));
	if (!split)
		return (cmd_free_memory(res, r_s));
	if (!ft_strlcpy(split, *s, strlen_mod(*s, c) + 1))
	{
		free (split);
		return (cmd_free_memory(res, r_s));
	}
	*s += strlen_mod(*s, c) + 1;
	*(res++) = split;
	return (res);
}

static char	**normal_args(char **res, char const **s, char **r_s)
{
	char	c;

	c = ' ';
	if (strlen_mod(*s, ' ') > strlen_mod(*s, '\''))
		c = '\'';
	*(res++) = malloc(sizeof(char) * (strlen_mod(*s, c) + 1));
	if (!*(res - 1))
	{
		cmd_free_memory(res - 1, r_s);
		return (NULL);
	}
	if (!ft_strlcpy(*(res - 1), *s, strlen_mod(*s, c) + 1))
		return (NULL);
	*s += strlen_mod(*s, c);
	return (res);
}

static int	cmd_count_words(char const *s)
{
	int		i;
	int		count;

	i = 0;
	count = 1;
	while (s[i] != '\0')
	{
		if (s[i] == '\'')
		{
			if (i > 0)
				count++;
			i++;
			while (s[i] != '\'' && s[i])
				i++;
			i++;
		}
		if (i > 0 && s[i] != ' ' && s[i - 1] == ' ')
			count++;
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
