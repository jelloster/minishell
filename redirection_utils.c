#include "minishell.h"

static int	is_redirection(char *str, size_t len);
static int	is_out_redirection(char *str, size_t len);
static int assign_redirection_type(t_cmd *cmd, int len, int i);
static int	parse_redir_args(t_cmd *cmd, char **paths, int redirs);

int	handle_redirected_cmd(t_cmd *cmd, char **paths)
{
	int	i;
	int	len;
	int	redirs;

	i = 0;
	redirs = 0;
	while (cmd->args[i])
	{
		len = ft_strlen(cmd->args[i]);
		if (is_redirection(cmd->args[i], len))
		{ 
			if (!assign_redirection_type(cmd, len, i))
				return (0);
			redirs++;
		}
		i++;
	}
	if (redirs > 2)
		return (0);
	return (parse_redir_args(cmd, paths, redirs));
}

/*
 * Checks that :
 * - the redirection symbol is not the last string in the args
 * - there are no 2 redirection symbols after each other
 * - there is only 1 redirection for output and input
 */
static int assign_redirection_type(t_cmd *cmd, int len, int i)
{
	if (!ft_strncmp(">", cmd->args[i], len) && cmd->outredir == NONE
		&& cmd->args[i + 1] && !is_redirection(cmd->args[i + 1], len))
		cmd->outredir = REPLACE;
	else if (!ft_strncmp("<", cmd->args[i], len) && cmd->inredir == NONE
		&& cmd->args[i + 1] && !is_redirection(cmd->args[i + 1], len))
		cmd->inredir = INPUT;
	else if (!ft_strncmp(">>", cmd->args[i], len) && cmd->outredir == NONE
		&& cmd->args[i + 1] && !is_redirection(cmd->args[i + 1], len))
		cmd->outredir = ADD;
	else if (!ft_strncmp("<<", cmd->args[i], len) && cmd->inredir == NONE
		&& cmd->args[i + 1] && !is_redirection(cmd->args[i + 1], len))
		cmd->inredir = STD_IN;
	else
		return (0);
	return (1);
}

// file always comes after the redir (unless std int??)
static int	parse_redir_args(t_cmd *cmd, char **paths, int redirs)
{
	char	**new_args;
	int	i;
	int	n_i;
	int	len;

	i = 0;
	n_i = 0;

	// Malloc for new args minus redirection symbols and files
	new_args = malloc((strstrlen(cmd->args) - redirs * 2 + 1) * sizeof(char *));
	if (!new_args)
		return (0);

	// Iterate through args
	while (cmd->args[i])
	{
		len = ft_strlen(cmd->args[i]);

		// If we come across a redirection symbol
		if (is_redirection(cmd->args[i], len))
		{

			// Set the str after as the in/outfile
			if (is_out_redirection(cmd->args[i], len))
				cmd->outfile = cmd->args[++i];
			else
				cmd->infile = cmd->args[++i];

			// Free the symbol string
			free (cmd->args[i - 1]);
			i++;
		}
		// Otherwise just copy the string over
		else
			new_args[n_i++] = cmd->args[i++];
	}
	new_args[n_i] = NULL; // buffer overflow
	free(cmd->args);
	cmd->args = new_args;
	return (extract_pathed_cmd(cmd, paths));
}

int	check_for_redirections(t_cmd *cmd)
{
	if (str_in_array_of_strs(">", cmd->args))
		return (1);
	else if (str_in_array_of_strs("<", cmd->args))
		return (1);
	else if (str_in_array_of_strs(">>", cmd->args))
		return (1);
	else if (str_in_array_of_strs("<<", cmd->args))
		return (1);
	return (0);
}

static int	is_redirection(char *str, size_t len)
{
	if (!ft_strncmp(">", str, len))
		return (1);
	else if (!ft_strncmp("<", str, len))
		return (1);
	else if (!ft_strncmp(">>", str, len))
		return (1);
	else if (!ft_strncmp("<<", str, len))
		return (1);
	return (0);
}

static int	is_out_redirection(char *str, size_t len)
{
	if (!ft_strncmp(">", str, len))
		return (1);
	else if (!ft_strncmp(">>", str, len))
		return (1);
	return (0);
}
