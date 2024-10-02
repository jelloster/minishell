#include "../inc/libft.h"

size_t	count_char_str(char c, char *str)
{
	size_t	count;

	while (str)
	{
		if (*str == c)
			count++;
		str++;
	}
	return (count);
}
