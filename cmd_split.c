#include "minishell.h"

static int		cmd_count_words(char const *s);
static void		*cmd_free_memory(char **res, char **r_s);
//static char		**normal_args(char **arg, char const **s, char **r_s);
//static char		**quoted_args(char **res, char const **s, char **r_s, char c);
//

char	*arg_cpy(char **res, char const **s, char **r_s);
int	arg_strcpy(const char *from, char *to);
int	arg_strlen(char *s);
int	arg_total_strlen(char *s);
int	has_quote_pair(char *s, char quote, int len);

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
		/*
		if (*s == '\'' || *s == '\"')
			res = quoted_args(res, &s, res_start, *s); // echo he"he"!!
		if (*s != ' ' && *s != '\0')
			res = normal_args(res, &s, res_start); */
		if (!*res)
			return (NULL);
		res++;
	}
	*res = NULL;
	return (res_start);
}

char	*arg_cpy(char **res, char const **s, char **r_s)
{
	char	*arg;
	int	len;

	len = arg_strlen((char *)*s);
	arg = malloc(sizeof(char) * (len + 1));
	if (!arg)
		return (cmd_free_memory(res, r_s));
	arg_strcpy(*s, arg);
	*s += arg_total_strlen((char *)*s); // ? 
	*(res++) = arg; // doesnt move res in cmd_split?
	printf("arg : %s.\n", arg);
	return (arg);
}

int	arg_strcpy(const char *from, char *to)
{
	char	quote;

	while (*from != ' ' && *from)
	{
		if (*from != '\'' && *from != '\"')
			*to++ = *from++;
		else
		{
			quote = *from;
			if (has_quote_pair((char *)from, quote, 0))
			{
				from++;
				while (*from != quote)
					*to++ = *from++;
				from++;
			}
			else
				return (-1);
		}
	}
	*to = '\0';
	return (1);

}

int	arg_strlen(char *s)
{
	int	len;
	int	quote_n;
	char	quote;

	len = 0;
	quote_n = 0;
	while (s[len] != ' ' && s[len])
	{
		if (s[len] != '\'' && s[len] != '\"')
			len++;
		else
		{
			quote = s[len];
			if (has_quote_pair(s, quote, len))
			{
				len++;
				while (s[len] != quote)
					len++;
				quote_n += 2;
				len++;
			}
			else
				return (-1); // ?
		}
	}
	printf("arg_stlen : %d.\n", len - quote_n);
	return (len - quote_n);
}

int	arg_total_strlen(char *s)
{
	int	len;
	char	quote;

	len = 0;
	while (s[len] != ' ' && s[len])
	{
		if (s[len] != '\'' && s[len] != '\"')
			len++;
		else
		{
			quote = s[len];
			if (has_quote_pair(s, quote, len))
			{
				len++;
				while (s[len] != quote)
					len++;
				len++;
			}
			else
				return (-1); // ?
		}
	}
	return (len);
}
int	has_quote_pair(char *s, char quote, int len)
{
	len++;
	while (s[len])
	{
		if (s[len] == quote)
			return (len);
		len++;
	}
	return (0);
}

/*
static char	**quoted_args(char **res, char const **s, char **r_s, char c)
{
	char	*res_str;
	int	len;

	(*s)++;
	len = strlen_quotes(*s, c);
	res_str = malloc(sizeof(char) * (len + 1));
	if (!res_str)
		return (cmd_free_memory(res, r_s));
	quoted_strcpy(*s, res_str, c); // how can this fail?
	if ((*s)[len] != '\0')
		*s += ft_strlen(*s);
	*(res++) = res_str;
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
*/
// count is wrong echo "-n hello wassup"
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
	printf("word count : %d\n.", count);
	return (count);
}

static void	*cmd_free_memory(char **res, char **res_start)
{
	while (res > res_start)
		free(*(--res));
	free(res_start);
	return (NULL);
}
