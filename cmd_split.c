/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motuomin <motuomin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 15:28:56 by motuomin          #+#    #+#             */
/*   Updated: 2024/12/09 11:50:21 by motuomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cmd_count_words(char const *s);
static int	iterate_quoted_word(char const *s, int *i, char quote);

/*
 * Function : cmd_split
 *
 * Splits the command line (s) into arguments while handling quoted
 * sections. Returns a NULL-terminated array of strings, or NULL on
 * failure.
*/

char	**cmd_split(char const *s)
{
	char	**res;
	char	**res_start;
	int		count;

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
		if ((*s && !arg_cpy(res++, &s, res_start)))
			return (NULL);
	}
	*res = NULL;
	return (res_start);
}

/*
 * Function : cmd_count_words
 *
 * Calculates how many arguments are in the command line string (s).
 * Treats quoted sections as single words.
 * Returns the count or -1 in case of unclosed quotes.
*/

static int	cmd_count_words(char const *s)
{
	int		i;
	int		count;

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
			if (!iterate_quoted_word(s, &i, s[i]))
				return (-1);
		}
		else if (i > 0 && s[i] != ' ' && s[i - 1] == ' ')
			count++;
		if (s[i])
			i++;
	}
	return (count);
}

/*
 * Function : iterate_quoted_word
 *
 * Advances the index (i) past a quoted word in (s).
 * Returns 1 if successful and 0 in the case of an unclosed quote.
*/

static int	iterate_quoted_word(char const *s, int *i, char quote)
{
	(*i)++;
	while (s[*i] && s[*i] != quote)
		(*i)++;
	return (s[*i] != '\0');
}
