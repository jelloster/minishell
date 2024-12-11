/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_cpy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motuomin <motuomin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 15:11:59 by motuomin          #+#    #+#             */
/*   Updated: 2024/12/10 18:34:34 by jkarhu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	has_quote_pair(char *s, char quote, int len);
static void	arg_strcpy(const char *from, char *to);
static int	arg_strlen(char *s);
static int	arg_total_strlen(char *s);

/*
 * Function : arg_cpy
 *
 * Copies the next argument from string (s) into the array (res).
 * Returns the copied argument or NULL in case of error.
*/

char	*arg_cpy(char **res, char const **s, char **r_s)
{
	char	*arg;

	arg = malloc(sizeof(char) * (arg_strlen((char *)*s) + 1));
	if (!arg)
		return (cmd_free_memory(res, r_s));
	arg_strcpy(*s, arg);
	*s += arg_total_strlen((char *)*s);
	*res = arg;
	return (arg);
}

/*
 * Function : arg_strcpy
 *
 * Copies the next argument from "from" into string "to",
 * excluding closed quotes.
 * Example:
 *	from : "he'l"'lo' world
 *	to : he'llo
 */

static void	arg_strcpy(const char *from, char *to)
{
	char	quote;
	
	printf("from : %s.\n", from);
	while (*from && *from != ' ')
	{
		if (*from != '\'' && *from != '\"')
			*to++ = *from++;
		else
		{
			quote = *from;
			from++;
			while (*from != quote && *from)
			{
<<<<<<< HEAD
				if (quote == '\'' && *from == '$')
				{
					*to++ = '\xFF';
					from++;
				}
				else
					*to++ = *from++;
=======
				//check_for_dollar(from, quote);
				/*
				if (--*from == ''' && ++*from == '$')
				{
					
				}
				*/
				// finds a dollar
				// if (!single_quote)
				/*
				{
					// "lalal $PWD"
					lalal /sefs/drdfgdf
					new_string = malloc(ft_strlen(envp[j] + 
				}*/
				*to++ = *from++;
>>>>>>> 4faca8b57542c304225463908161aca6ec1c7175
			}
			if (*from)
				from++;
		}
	}
	*to = '\0';
}

/*
 * Function : arg_strlen
 *
 * Calculates the lenght of the next argument in string "s"
 * excluding closed quotes.
 * Example:
 *	s: "hel""lo" -n
 *	len : 5
 */

static int	arg_strlen(char *s)
{
	int		len;
	int		quote_n;
	char	quote;

	len = 0;
	quote_n = 0;
	while (s[len] && s[len] != ' ')
	{
		if (s[len] != '\'' && s[len] != '\"')
			len++;
		else
		{
			quote = s[len];
			if (has_quote_pair(s, quote, len++))
			{
				while (s[len] && s[len] != quote)
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

/*
 * Function : arg_total_strlen
 *
 * Calculates the total length of the next argument
 * in string "s" including quotes.
 * Example:
 *	s: "hello hi" -n
 *	len : 10 (len of "hello hi")
 */

static int	arg_total_strlen(char *s)
{
	int		len;
	char	quote;

	len = 0;
	while (s[len] && s[len] != ' ')
	{
		if (s[len] != '\'' && s[len] != '\"')
			len++;
		else
		{
			quote = s[len++];
			while (s[len] && s[len] != quote)
				len++;
			len++;
		}
	}
	return (len);
}

/*
 * Function : has_quote_pair
 *
 * Checks if a quote character in a string (s) has a closing
 * pair. Returns the position of the closing quote if found,
 * 0 otherwise.
 *
 * Example: 
 *	s: echo "hello
 *	returns 0 (no closing quote)
 *	s: echo "hello"
 *	returns > 0 (position of closing quote)
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
