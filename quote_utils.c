#include "minishell.h"

/*
int	count_quoted_words(char const *s, int *i)
{
	int	count;
	char	q;

	count = 0;

	// Save wether single or double quote
	q = s[*i];

	// Add 1 to count if it's not the first word
	if (*i > 0)
		count++;

	// Move past the quote
	(*i)++;

	// Iterate to the quote pair
	while (s[*i] != q && s[*i])
		(*i)++;
	// If quote pair not found, return -1
	if (!s[*i])
		return (-1);

	// If there next char isn't a space, move to the end
	if (s[*i] != ' ' && s[*i])
		while (s[*i] != ' ' && s[*i])
			(*i)++;
	return (count);
}
*/

int	strlen_quotes(char const *s, char q)
{
	int	len;
	int	quotes;
	
	len = 0;
	quotes = 0;
	while (s[len] != q && s[len])
		len++;
	while (s[len] != ' ' && s[len])
	{
		if (s[len] == '\'' || s[len] == '\"')
			quotes++;
		len++;
	}
	printf("strlen_quotes : %d\n", len - quotes);
	return (len - quotes);
}

char	*quoted_strcpy(const char *from, char *to, char q)
{
	while (*from != q && *from)
		*to++  = *from++;
	while (*from != ' ' && *from)
	{
		if (*from != '\'' && *from != '\"')
			*to++  = *from++;
		else
			from++;
	}
	*to = '\0';
	return (to);
}
