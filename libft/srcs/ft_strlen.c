/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motuomin <motuomin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:51:43 by motuomin          #+#    #+#             */
/*   Updated: 2025/01/16 14:02:53 by motuomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Description : computes the length of the string s.  The strnlen() function
 * attempts to compute the length of s, but never scans beyond the first maxlen
 * bytes of s. */

#include <stddef.h>

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s && s[len] != '\0')
		len++;
	return (len);
}
