/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motuomin <motuomin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:59:36 by motuomin          #+#    #+#             */
/*   Updated: 2024/11/04 16:21:52 by motuomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	strlen_mod(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] != c && s[i] != '\0')
		i++;
	return (i);
}

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

int	strstrlen(char **strs)
{
	int	len;

	len = 0;
	if (strs)
		while (strs[len])
			len++;
	return (len);
}
