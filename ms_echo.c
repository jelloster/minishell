void	ms_echo(char *str, int flag, int fd)
{
	ft_printf("%s", str);
	if (flag)
		ft_printf("\n");
}
