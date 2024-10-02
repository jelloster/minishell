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

# include "libft/inc/libft.h"

// --- TYPEDEFS ---

typedef enum e_operator
{
	NONE,
	PIPE,
	REPLACE,
	ADD,
	INPUT,
	STD_IN,
}	t_operator;

typedef struct s_cmd
{
	char	**args;
	char	*pathed_cmd;
}	t_cmd;

typedef struct s_ast
{
	void		*content; // t_cmd or operator
	t_operator	operator;
	t_cmd		*cmd;
	struct s_ast	*left;
	struct s_ast	*right;
	struct s_ast	*next;
}	t_ast;

typedef struct s_ms
{
	char	*program_name;
	char	**envp;
	char	**paths;
	char	**history;
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

// --- FUNCTION PROTOTYPES ---

//	init_ms.c
int	init_ms(int ac, char *av[], char *envp[], t_ms *ms);

//	Builtin functions
//	ms_echo.c
void	ms_echo(char *str, int flag, int fd);

// move to libft
size_t	count_strs(char **strs);

//	exe_cmd.c
void	exe_cmd(t_cmd cmd, char *envp[]);

//	print_utils.c
void	print_in_color(const char *str, t_color color);
void	clear_terminal(void);

//	envp_utils.c
char	**extract_paths(char *envp[]);

//	parsing.c
int	parse(char *cmd_line, t_ms *ms);

//	cmd_split.c
char	**cmd_split(char const *s);

//	str_utils.c
size_t	strlen_mod(char const *s, char c);
int	free_array_of_arrays(char **arr);

//	cmd_line.c
int	extract_command(char *cmd_line, t_ms *ms, t_cmd *cmd);

#endif
