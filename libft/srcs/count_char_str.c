/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_char_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motuomin <motuomin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:57:39 by motuomin          #+#    #+#             */
/*   Updated: 2024/12/09 16:57:41 by motuomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

size_t	count_char_str(char c, char *str)
{
	size_t	count;

	count = 0;
	while (str)
	{
		if (*str == c)
			count++;
		str++;
	}
	return (count);
}
