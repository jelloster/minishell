static void	handle_escape_sequence(char **str, int fd);

/*
 * Function: ms_echo
 *
 * Params:
 * - str (string to be echoed)
 * - flag (if the -e flag is used or not)
 * - fd (where the string is echoed)
 */

// IT IS THE -n FLAG

void	ms_echo(char *str, int flag, int fd)
{
	if (flag) // could wigure out within function. take t_cmd.
	{
		while (*str)
		{
			if (*str == '\\')
				handle_escape_sequence(&(++str), fd);
			else
				ft_putchar_fd(*str, fd);
			str++;
		}
	}
	else
		ft_putstr_fd(str, fd);
}

static void	handle_escape_sequence(char **str, int fd)
{
	if (**str == 'a')
		ft_putchar_fd('\a', fd);
	else if (**str == 'b')
		ft_putchar_fd('\b', fd);
	else if (**str == 'c')
		ft_putchar_fd('\c', fd);
	else if (**str == 'e')
		ft_putchar_fd('\e', fd);
	else if (**str == 'f')
		ft_putchar_fd('\f', fd);
	else if (**str == 'n')
		ft_putchar_fd('\n', fd);
	else if (**str == 'r')
		ft_putchar_fd('\r', fd);
	else if (**str == 't')
		ft_putchar_fd('\t', fd);
	else if (**str == 'v')
		ft_putchar_fd('\v', fd);
	else if (**str == '\\')
		ft_putchar_fd('\\', fd);
	else
	{
		ft_putchar_fd('\\', fd);
		ft_putchar_fd(**str, fd);
	}
}

/*
static t_bool char_in_str(char c, const char *str)
{
	while (str)
	{
		if (c == *str)
			return (TRUE);
		str++;
	}
	return (FALSE);
} */

	/*
	else if (ft_strncmp("0nnn", *str, 4) == 0)
		ft_putchar_fd('\0nnn', fd);
	else if (ft_strncmp("xHH", *str, 4) == 0)
		retrun (TRUE);
	else if (ft_strncmp("uHHHH", *str, 4) == 0)
		retrun (TRUE);
	else if (ft_strncmp("UHHHHHHHH", *str, 4) == 0)
		retrun (TRUE);
	*/
