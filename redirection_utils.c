#include "minishell.h"

static int	command_first(t_cmd *cmd, int red, char **paths);
static int	command_last(t_cmd *cmd, char **paths);
static int	is_redirection(char *str, size_t len);


// WHAT IF THERE ARE MANY REDIRECTION IN A PIPE

int	handle_redirected_cmd(t_cmd *cmd, char **paths)
{
	int	i;
	int	len;

	i = 0;
	while (!is_redirection(cmd->args[i], ft_strlen(cmd->args[i])))
		i++;
	len = ft_strlen(cmd->args[i]);
	if (!ft_strncmp(">", cmd->args[i], len))
		cmd->redir = REPLACE;
	else if (!ft_strncmp("<", cmd->args[i], len))
		cmd->redir = INPUT;
	else if (!ft_strncmp(">>", cmd->args[i], len))
		cmd->redir = ADD;
	else if (!ft_strncmp("<<", cmd->args[i], len))
		cmd->redir = STD_IN;
	if (i == 0)
		return (command_last(cmd, paths));
	else
		return (command_first(cmd, i, paths));
}

/* Function : command_first
 *
 * Description : Fills in the t_cmd struct for commands in 
 * format: "echo hello >> file.txt"
 *
 * Before : 
 * args = ["echo" "hello" ">>" "file.txt"];
 * file = NULL;
 * redirection = ADD;
 * 
 * After :
 * args = ["echo" "hello"];
 * file = "file.txt";
 * redirection = ADD;
 * 
*/

// IF NOT IN A PIPE THERE COULD BE 2 REDIRECTIONS
// file < cmd > file

static int	command_first(t_cmd *cmd, int red, char **paths)
{
	char	**new_args;
	int	i;

	new_args = malloc((red + 1) * sizeof(char *));
	if (!new_args)
		return (0);
	new_args[red] = NULL;
	cmd->file = ft_strdup(cmd->args[red + 1]);
	if (!cmd->file)
	{
		free_array_of_arrays(new_args);
		return (0);
	}
	i = -1;
	while (++i < red)
		new_args[i] = cmd->args[i];
	free(cmd->args);
	cmd->args = new_args;
	return (extract_pathed_cmd(cmd, paths));
}

/* Function : command_last
 *
 * Description : Fills in the t_cmd struct for commands in 
 * format: ">> file.txt echo hello"
 *
 * Before : 
 * args = [">>" "file.txt" "echo" "hello"];
 * file = NULL;
 * redirection = ADD;
 * 
 * After :
 * args = ["echo" "hello"];
 * file = "file.txt";
 * redirection = ADD;
 * 
*/

static int	command_last(t_cmd *cmd, char **paths)
{
	char	**new_args;
	int	i;
	int	len;

	len = 0;
	while (cmd->args[len])
		len++;
	if (len < 3)
		return (0); // handle // no command
	cmd->file = ft_strdup(cmd->args[1]); // make sure no segfault
	if (!cmd->file)
		return (0);
	new_args = malloc((len - 2 + 1) * sizeof(char *));
	if (!new_args)
	{
		free (cmd->file);
		return (0);
	}
	new_args[len - 2] = NULL;
	i = -1;
	while (++i < len - 2)
		new_args[i] = cmd->args[2 + i];
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
