/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_cpy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motuomin <motuomin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 15:11:59 by motuomin          #+#    #+#             */
/*   Updated: 2024/12/16 15:50:35 by motuomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	arg_strcpy(const char *from, char *to);
static int	arg_strlen(char *s);
static int	arg_total_strlen(char *s);

static char	*copy_symbol(char const **s)
{
	char	*str;

	str = NULL;
	if (**s == '|')
		str = ft_strdup ("|");
	else if (!ft_strncmp(*s, ">>", 2))
		str = ft_strdup (">>");
	else if (!ft_strncmp(*s, "<<", 2))
		str = ft_strdup ("<<");
	else if (!ft_strncmp(*s, ">", 1))
		str = ft_strdup (">");
	else if (!ft_strncmp(*s, "<", 1))
		str = ft_strdup ("<");
	*s += ft_strlen(str);
	return (str);
}

/*
 * Function : arg_cpy
 *
 * Copies the next argument from string (s) into the array (res).
 * Returns the copied argument or NULL in case of error.
*/

char	*arg_cpy(char **res, char const **s, char **r_s)
{
	char	*arg;

	if (**s == '|' || !ft_strncmp(*s, ">>", 2) || !ft_strncmp(*s, "<<", 2)
		|| !ft_strncmp(*s, "<", 1) || !ft_strncmp(*s, ">", 1))
	{
		arg = copy_symbol(s);
		if (!arg)
			return (cmd_free_memory(res, r_s));
	}
	else
	{
		arg = malloc(sizeof(char) * (arg_strlen((char *)*s) + 1));
		if (!arg)
			return (cmd_free_memory(res, r_s));
		arg_strcpy(*s, arg);
		*s += arg_total_strlen((char *)*s);
	}
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

	while (*from && *from != ' ' && *from != '\t'
		&& *from != '|' && *from != '>' && *from != '<')
	{
		if (*from != '\'' && *from != '\"')
			*to++ = *from++;
		else
		{
			quote = *(from++);
			while (*from != quote && *from)
			{
				if (quote == '\'' && *from == '$')
				{
					*to++ = '\xFF';
					from++;
				}
				else
					*to++ = *from++;
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
	while (s[len] && s[len] != ' ' && s[len] != '\t'
		&& s[len] != '|' && s[len] != '>' && s[len] != '<')
	{
		if (s[len] != '\'' && s[len] != '\"')
			len++;
		else
		{
			quote = s[len++];
			while (s[len] && s[len] != quote)
				len++;
			len++;
			quote_n += 2;
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
	while (s[len] && s[len] != ' ' && s[len] != '\t'
		&& s[len] != '|' && s[len] != '>' && s[len] != '<')
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
