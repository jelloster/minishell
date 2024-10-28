#include "minishell.h"

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
	int		len;
	int		quote_n;
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
