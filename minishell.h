/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motuomin <motuomin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:46:38 by motuomin          #+#    #+#             */
/*   Updated: 2025/01/18 16:40:58 by motuomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// --- INCLUDES ---

// - LIBRARIES -

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <fcntl.h>
# include <signal.h>
# include <errno.h>
# include <sys/stat.h>
# include <termio.h>

// - HEADER FILES -

# include "libft/inc/libft.h"

// --- TYPEDEFS ---

typedef enum e_redir
{
	NONE,
	PIPE,
	REPLACE,
	ADD,
	INPUT,
	STD_IN,
}	t_redir;

typedef enum e_error_code
{
	COMMAND_NOT_FOUND = 1,
	FILE_NOT_FOUND,
	PERMISSION_DENIED,
	IS_DIRECTORY,
}	t_error_code;

typedef struct s_cmd
{
	char	**args;
	char	*pathed_cmd;
	char	*infile;
	char	**infiles;
	int		infile_n;
	char	**outfiles;
	int		outfile_n;
	char	*outfile;
	char	**envp;
	char	*pn;
	int		o_i;
	int		i_i;
	int		hd;
	t_redir	outredir;
	t_redir	inredir;
	t_redir	*inredirs;
}	t_cmd;

typedef struct s_shell_var
{
	char				*key;
	char				*value;
	int					is_exported;
	struct s_shell_var	*next;
}	t_shell_var;

typedef struct s_ms
{
	char		*program_name;
	char		**envp;
	char		**paths;
	char		*cmd_line;
	t_cmd		*cmds;
	int			nlen;
	int			error;
	int			cmd_n;
	int			parsed_cmds;
	int			ret_val;
	int			temp_ret;
	int			fds[2];
	char		**split;
	int			dont;
	t_shell_var	*shell_vars;
}	t_ms;

typedef enum e_color
{
	RED,
	GREEN,
	YELLOW,
	BLUE,
	MAGENTA,
	CYAN,
	RESET,
}	t_color;

// --- MACROS ---

# define WELCOME_MSG "\n ✧.* Welcome to MINISHELL! ✧.*\n\n"
# define CNF COMMAND_NOT_FOUND
# define FNF FILE_NOT_FOUND
# define PD PERMISSION_DENIED
# define ID IS_DIRECTORY

extern int	g_sig;

/* --- FUNCTION PROTOTYPES --- */

/* - Minishell initialization - */

//			init_ms.c
int			init_ms(int ac, char *av[], char *envp[], t_ms *ms);
void		update_shlvl(t_ms *ms, int sign);
char		**allocate_and_copy_envp(char **envp, int size, int extra_space);

//			envp_utils.c
char		**extract_paths(char *envp[]);

/* - Command line parsing - */

//			parsing.c
t_cmd		*parse(char *cmd_line, t_ms *ms);
int			extract_pathed_cmd(t_cmd *cmd, char **paths);

//			parsing_utils.c
size_t		count_cmds(char **split);
int			free_n_exit(char *p_cmd, char *s_cmd, char **args, int ret);
void		init_cmd(t_cmd *cmd, t_ms *ms);
int			c_a_f_p(t_cmd *cmd, char **split, size_t size, t_ms *ms);

//			arg_cpy.c
char		*arg_cpy(char **res, char const **s, char **r_s);

//			cmd_split.c
char		**cmd_split(char const *s);

/* - Command exection & pipes - */

//			exe_cmd.c
int			exe_cmd(t_cmd *cmd, t_ms *ms);

//			pipex/pipex.c
int			pipex(t_cmd *cmds, t_ms *ms);

//			pipex/pipe_utils.c
int			redirect_input(char *file, t_cmd *cmd);
int			redirect_output(char *file, t_cmd *cmd);

/* - Builtin functions - */

//			history.c
int			update_history(t_ms *ms, char *cmd_line);

//			redirection_utils.c
int			handle_redirected_cmd(t_ms *ms, t_cmd *cmd, char **paths);
int			check_for_redirections(t_cmd *cmd);

int			has_quote_pair(char *s, char quote, int len);

//			heredoc_handle.c
int			heredoc_write(const char *delim, t_ms *ms, t_cmd *cmd);
int			heredoc_print(t_cmd *cmd);

//			memory_functions.c
int			free_cmds(t_cmd *cmds, int cmd_n);
int			free_ms(t_ms *ms, char *cmd_line, t_cmd *cmds, int ret);
void		*cmd_free_memory(char **res, char **res_start);
void		*free_array_of_arrays(char **arr);

//			free_shell.c
void		free_shell_vars(t_shell_var **shell_vars);

int			update_paths(t_ms *ms);
//			print_export.c
void		print_exported_vars(t_ms *ms, t_shell_var *shell_vars);

//			env_sort.c
char		**sort_env(char **msenvp);
int			count_env(char **msenvp);

//			handle_key_value.c
int			handle_key_value(char *arg, t_ms *ms, t_shell_var **shell_vars);

//			built_ins.c
int			cd_built_in(char **args, t_ms *ms);
int			echo_built_in(t_cmd *cmd, t_ms *ms, char **args);
void		dollar_check(t_ms *ms, char **args);
int			unsetenv_manual(const char *key, char **envp);
int			unset_built_in(char **args, t_ms *ms);
int			setenv_update(const char *key, const char *value, t_ms *ms);

// testing built ins.c
char		*get_env_value(t_ms *ms, const char *key, int custom_len);
char		*free_on_error(char **split_words, char *result);

int			pwd_built_in(char **msenvp, t_cmd *cmd);
int			env_built_in(char **msenvp, t_cmd *cmd);
int			add_shell_var(t_shell_var **shell_vars, char *key, char *value);
void		remove_shell_var(t_shell_var **shell_vars, char *key);
void		init_shell_vars(char **envp, t_shell_var **shell_vars);

int			export_built_in(char **args, t_ms *ms, t_shell_var **shell_vars);
void		print_shell_vars(t_shell_var *shell_vars, t_ms *ms);
void		print_env_vars(char **msenvp);
int			key_legit_check(char *arg);

t_shell_var	*find_shell_var(t_shell_var *shell_vars, const char *key);
char		*get_key(char *envp);

//			built_in_utils.c
int			is_built_in(const char *cmd);
int			exe_built_in(t_cmd *cmd, t_ms *ms);

/* - Miscellaneous - */

t_cmd		*syntax_error(char **split, t_ms *ms);
//			error_utils.c
void		err(t_ms *ms);

//			print_utils.c
void		print_in_color(const char *str, t_color color);
void		clear_terminal(void);

//			str_utils.c
size_t		strlen_mod(char const *s, char c);
int			str_in_array_of_strs(char *str, char **strs);
int			strstrlen(char **strs);

//			signal.c
void		handle_sigint(int signal);
//void		handle_sigquit(int signal);
void		handle_signals(void);

int			is_out_redirection(char *str, size_t len);

//			pipex/error_utils.c
void		error_msg(int error, char *str, char *binary);
void		print_and_clear_errorlog(void);

int			find_last(char *str, char c);
void		exit_built_in(t_cmd *cmd, t_ms *ms);

//			echo_built_in.c
void		handle_squiggly(char *arg, int *j, int fd, t_ms *ms);
int			handle_flag(char **args);
int			malloc_for_redirs(t_cmd *cmd);

//			syntax_check.c
int			syntax_check(char **split);

void		delete_error_log(void);

//			dollarquestion.c
void		dollarquestion(t_ms *ms, t_cmd *cmd);
void		free_cmd(t_cmd *cmds, int i);
void		setup_inredir_arr(t_cmd *cmd);
int			is_redirection(char *str, size_t len);

void		sigint_child(int signal);
void		sigint_aftercat(int signal);
int			expand(t_cmd *cmds, t_ms *ms);
int			expand_args(t_cmd *cmd, t_ms *ms);

void		remove_sigint_heredoc(t_cmd *cmds, t_ms *ms);
int			strlen_specialchar(char *s);
void		update_sig_ret_val(t_ms *ms);
void		here_doc_file_thing(t_cmd *cmd, int *i);

#endif
