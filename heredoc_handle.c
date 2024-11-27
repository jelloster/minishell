#include "minishell.h"

int	heredoc_write(const char *delim, t_cmd *cmd)
{
	int		temp_fd;
	char	*line;

	temp_fd = open(".heredoc_temp", O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (temp_fd == -1)
	{
		perror("open write");
		return (0);
	}
	while (1)
	{
		line = readline("> ");
		if (!line || strcmp(line, delim) == 0)
		{
			free(line);
			break ;
		}
		write(temp_fd, line, strlen(line));
		write(temp_fd, "\n", 1);
		free(line);
	}
	close(temp_fd);
	cmd->inredir = STD_IN;
	cmd->infile = ft_strdup(".heredoc_temp");
	return (1);
}

int	heredoc_print(t_cmd *cmd)
{
	int		fd;
	char	*line;
	
	fd = open(cmd->infile, O_RDONLY);
	if (fd == -1)
	{
		perror("open print");
		return (0);
	}
	while ((line = get_next_line(fd)))
	{
		ft_printf("%s", line);
		free(line);
	}
	close(fd);
	return (1);
}
