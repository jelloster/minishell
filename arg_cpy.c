/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_cpy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motuomin <motuomin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 15:11:59 by motuomin          #+#    #+#             */
/*   Updated: 2024/10/28 15:28:03 by motuomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	has_quote_pair(char *s, char quote, int len);

/*
 * Copies the arg (without the quotes)
 * E.g.,:
 * from : "hel""lo"
 *
 * After copying to to:
 * to : hello
 */

void	arg_strcpy(const char *from, char *to)
{
	char	quote;

	while (*from != ' ' && *from)
	{
		if (*from != '\'' && *from != '\"')
			*to++ = *from++;
		else
		{
			quote = *from;
			from++;
			while (*from != quote)
				*to++ = *from++;
			from++;
		}
	}
	*to = '\0';
}

/*
 * Gets the len of an arg without quotes.
 *
 * E.g.,:
 * "hel""lo" > len : 5
 * hello > len : 5
 */

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
			if (has_quote_pair(s, quote, len++))
			{
				while (s[len] != quote)
					len++;
				quote_n += 2;
				len++;
			}
			else
				return (-1);
		}
	}
	return (len - quote_n);
}

/* Gets the total length of an arg (including quotes)
 *
 * E.g.,:
 * "hello" > len : 7
 *	hello > len : 5
 */

int	arg_total_strlen(char *s)
{
	int		len;
	char	quote;

	len = 0;
	while (s[len] != ' ' && s[len])
	{
		if (s[len] != '\'' && s[len] != '\"')
			len++;
		else
		{
			quote = s[len];
			len++;
			while (s[len] != quote)
				len++;
			len++;
		}
	}
	return (len);
}

/*
 * Checks if a quote character in a string (s) has a closing
 * counterpart. 
 *
 * E.g., : 
 * echo "hello   > returns < 0
 * echo "hello"  > returns > 0
 */

static int	has_quote_pair(char *s, char quote, int len)
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
