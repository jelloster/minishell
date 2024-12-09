/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_last.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motuomin <motuomin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:26:12 by motuomin          #+#    #+#             */
/*   Updated: 2024/12/09 14:35:34 by motuomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_last(char *str, char c)
{
	int	len;

	len = ft_strlen(str);
	while (--len >= 0)
	{
		if (str[len] == c)
			return (len);
	}
	return (len);
}
