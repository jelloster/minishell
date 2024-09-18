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

typedef struct s_cmd
{
	char	**args;
	char	*pathed_cmd;
}	t_cmd;

typedef struct s_ms
{
	int	ac;
	char	**av;
	char	**envp;
	char	**paths;
	char	**history;
}	t_ms;

// --- MACROS ---

// Colors codes
# define RESET	"\033[0m"
# define RED	"\033[31m"
# define GREEN	"\033[32m"
# define YELLOW	"\033[33m"
# define BLUE	"\033[34m"

// --- FUNCTION PROTOTYPES ---

//	envp_utils.c
char	**extract_paths(char *envp[]);

//	parsing.c
int	parse(int ac, char *av[], char *envp[], t_ms *ms);

//	cmd_split.c
char	**cmd_split(char const *s);

//	str_utils.c
size_t	strlen_mod(char const *s, char c);
int	free_array_of_arrays(char **arr);

//	cmd_line.c
int	extract_command(char *cmd_line, t_ms *ms, t_cmd *cmd);

#endif
