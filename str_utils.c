/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motuomin <motuomin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:59:36 by motuomin          #+#    #+#             */
/*   Updated: 2025/01/15 17:55:58 by motuomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Function: strlen_mod
 *
 * Returns the len of a str until a given character (c)
 * or to the end of the string.
*/

size_t	strlen_mod(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] != c && s[i] != '\0')
		i++;
	return (i);
}

/*
 * Function : str_in_array_of_strs
 *
 * Returns 1 if a given string (str) can be found in an array of strings (strs),
 * Returns 0 if not.
*/

int	str_in_array_of_strs(char *str, char **strs)
{
	int	i;
	int	len;

	i = 0;
	while (strs[i])
	{
		len = ft_strlen(strs[i]);
		if ((int)ft_strlen(str) > len)
			len = ft_strlen(str);
		if (ft_strncmp(str, strs[i], len) == 0)
			return (1);
		i++;
	}
	return (0);
}

/*
 * Function : strstrlen
 *
 * Calculates and returns the length of an array of strs
*/

int	strstrlen(char **strs)
{
	int	len;

	len = 0;
	if (strs)
		while (strs[len])
			len++;
	return (len);
}

int	strlen_specialchar(char *s)
{
	int	i;

	i = 0;
	while (s[i] && ft_isalnum(s[i]))
		i++;
	return (i);
}
