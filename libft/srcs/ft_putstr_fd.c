/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motuomin <motuomin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:28:13 by motuomin          #+#    #+#             */
/*   Updated: 2024/12/12 19:18:25 by jkarhu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Description : Outputs the string ’s’ to the given file descriptor.*/

#include <unistd.h>

void	ft_putstr_fd(char *s, int fd)
{
	int	len;

	while (s[len])
		len++;
	write(fd, s, len);
}
