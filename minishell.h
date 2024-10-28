#ifndef MINISHELL_H
# define MINISHELL_H

// --- INCLUDES ---

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>    // stat, lstat, fstat
# include <signal.h>      // signal, sigaction, sigemptyset, sigaddset, kill
# include <dirent.h>      // opendir, readdir, closedir
# include <string.h>      // strerror
# include <termios.h>     // tcsetattr, tcgetattr
# include <curses.h>      // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <sys/ioctl.h>   // ioctl
# include <readline/readline.h>
# include <readline/history.h>

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

typedef struct s_cmd
{
	char	**args;
	char	*pathed_cmd;
	char	*file;
	char	*infile; // < infile cat > outfile
	char	*outfile;
	char	**envp;
	t_redir	redir;

}	t_cmd;

typedef struct s_ms
{
	char	*program_name;
	char	**envp;
	char	**paths;
	char	**history;
	char	*cmd_line;
	int	his_n;
	int	error;
	int	cmd_n;
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

/*
typedef struct s_ast
{
	void		*content; // t_cmd or operator
	t_operator	operator;
	t_cmd		*cmd;
	struct s_ast	*left;
	struct s_ast	*right;
	struct s_ast	*next;
}	t_ast;

typedef enum e_operator
{
	NONE,
	PIPE,
	REPLACE,
	ADD,
	INPUT,
	STD_IN,
}	t_operator;
*/

// --- MACROS ---

# define WELCOME_MSG "\n ✧.* Welcome to MINISHELL! ✧.*\n\n"

/* --- FUNCTION PROTOTYPES --- */

/* - Minishell initialization - */

//	pipex/pipex.c
int	pipex(t_cmd *cmds, int cmd_n);
//	pipex/pipe_utils.c
void	redirect_input(char *file);
void	redirect_output(char *file);

//	quote_utils.c
int	count_quoted_words(char const *s, int *i);
int	strlen_quotes(char const *s, char q);
char	*quoted_strcpy(const char *from, char *to, char q);

//	init_ms.c
int	init_ms(int ac, char *av[], char *envp[], t_ms *ms);

/* - Builtin functions - */

//	ms_echo.c
void	ms_echo(char *str, int flag, int fd);

//	history.c
int	update_history(t_ms *ms, char *cmd_line);
/* - Command line parsing - */

int	arg_strcpy(const char *from, char *to);
int	arg_strlen(char *s);
int	arg_total_strlen(char *s);
int	has_quote_pair(char *s, char quote, int len);

//	parsing.c
t_cmd	*parse(char *cmd_line, t_ms *ms);
int	extract_pathed_cmd(t_cmd *cmd, char **paths);

//	parsing_utils.c
size_t	count_cmds(char **split);
int	free_n_exit(char *p_cmd, char *s_cmd, char **args, int ret);
void	init_cmd(t_cmd *cmd, t_ms *ms);

//	redirection_utils.c
int	handle_redirected_cmd(t_cmd *cmd, char **paths);
int	check_for_redirections(t_cmd *cmd);

//	cmd_split.c
char	**cmd_split(char const *s);


//	memory_functions.c
int	free_cmds(t_cmd *cmds, int cmd_n);

/* - Miscellaneous - */

//	exe_cmd.c
int	exe_cmd(t_cmd *cmd);

//	print_utils.c
void	print_in_color(const char *str, t_color color);
void	clear_terminal(void);

//	envp_utils.c
char	**extract_paths(char *envp[]);

//	str_utils.c
size_t	strlen_mod(char const *s, char c);
int	free_array_of_arrays(char **arr);
int	str_in_array_of_strs(char *str, char **strs);

#endif
