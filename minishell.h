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
# include <dirent.h>      // opendir, readdir, closedir

/*
# include <sys/stat.h>    // stat, lstat, fstat
# include <signal.h>      // signal, sigaction, sigemptyset, sigaddset, kill
# include <string.h>      // strerror
# include <termios.h>     // tcsetattr, tcgetattr
# include <curses.h>      // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <sys/ioctl.h>   // ioctl
*/

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

typedef struct s_cmd
{
	char	**args;
	char	*pathed_cmd;
	// char	*file;
	char	*infile; // < infile cat > outfile
	char	*outfile;
	char	**envp;
	//t_redir	redir; // what if 2 ? not allowd in pipe!
	t_redir outredir;
	t_redir inredir;
}	t_cmd;

typedef struct s_ms
{
	char	*program_name; // not used yet
	char	**envp;
	char	**paths;
	char	*cmd_line;
	int		error;
	int		cmd_n;
	int		parsed_cmds;
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

/* --- FUNCTION PROTOTYPES --- */

/* - Minishell initialization - */

//		init_ms.c
int		init_ms(int ac, char *av[], char *envp[], t_ms *ms);

//		envp_utils.c
char	**extract_paths(char *envp[]);

/* - Command line parsing - */

//		arg_cpy.c
void		arg_strcpy(const char *from, char *to);
int		arg_strlen(char *s);
int		arg_total_strlen(char *s);

//		cmd_split.c
char	**cmd_split(char const *s);

//		parsing.c
t_cmd	*parse(char *cmd_line, t_ms *ms);
int		extract_pathed_cmd(t_cmd *cmd, char **paths);

//		parsing_utils.c
size_t	count_cmds(char **split);
int		free_n_exit(char *p_cmd, char *s_cmd, char **args, int ret);
void	init_cmd(t_cmd *cmd, t_ms *ms);

/* - Command exection & pipes - */

//		exe_cmd.c
int		exe_cmd(t_cmd *cmd);

//		pipex/pipex.c
int		pipex(t_cmd *cmds, int cmd_n);

//		pipex/pipe_utils.c
void	redirect_input(char *file);
void	redirect_output(char *file);

/* - Builtin functions - */

//		ms_echo.c
void	ms_echo(char *str, int flag, int fd);

//		history.c
int		update_history(t_ms *ms, char *cmd_line);

//		redirection_utils.c
int		handle_redirected_cmd(t_cmd *cmd, char **paths);
int		check_for_redirections(t_cmd *cmd);

//		memory_functions.c
int		free_cmds(t_cmd *cmds, int cmd_n);

/* - Miscellaneous - */

//		print_utils.c
void	print_in_color(const char *str, t_color color);
void	clear_terminal(void);

//		str_utils.c
size_t	strlen_mod(char const *s, char c);
int		free_array_of_arrays(char **arr);
int		str_in_array_of_strs(char *str, char **strs);
int		strstrlen(char **strs);

#endif
