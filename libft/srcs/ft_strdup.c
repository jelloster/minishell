/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motuomin <motuomin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 09:21:49 by motuomin          #+#    #+#             */
/*   Updated: 2025/01/16 14:06:05 by motuomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Description : function copies at most n characters from the string s1 always
 * NUL teeminating the copied string. */

#include <stdlib.h>
#include "../inc/libft.h"

char	*ft_strdup(const char *s1)
{
	size_t		i;
	char		*ptr;

	i = 0;
	ptr = malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	while (s1 && s1[i] != '\0')
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
