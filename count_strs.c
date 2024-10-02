#include "minishell.h"

size_t	count_strs(char **strs)
{
	size_t	count;

	count = 0;
	while (strs[count++]) ;
	return (count);
}
