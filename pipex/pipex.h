/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motuomin <motuomin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:01:01 by motuomin          #+#    #+#             */
/*   Updated: 2025/01/13 17:05:43 by motuomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

// INCLUDES
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "../libft/inc/libft.h"
# include <errno.h>

# include "../../inc/minishell.h"

/*
typedef enum e_error_code
{
	COMMAND_NOT_FOUND = 1,
	FILE_NOT_FOUND,
	PERMISSION_DENIED,
}	t_error_code;
*/

// TYPEDEFS
typedef struct s_aae
{
	int		ac;
	char	**av;
	char	**envp;
	char	**paths;
}			t_aae;

/*
typedef struct s_cmd
{
	char	*av_str;
	char	*pathed_cmd;
	char	**args;
	t_aae	*aae;
}			t_cmd;
*/

// FUNCTION PROTOTYPES

//	command_extraction.c
int		extract_command(t_cmd *cmd);
//int		exe_cmd(t_cmd cmd);

//	pipe_utils.c
int		write_to_pipe(t_cmd cmd, int *fd, t_ms *ms);
int		read_and_write(t_cmd cmd, int fd_r, int fd_w, t_ms *ms);
int		read_from_pipe(t_cmd cmd, int fd, t_ms *ms);
int		wait_and_close(pid_t *pids, int cmd_n);

//	str_utils.c
size_t	strlen_mod(char const *s, char c);

//	awk_split.c
char	**awk_split(char const *s);

//	error_utils.c
void	fork_error(t_cmd *cmds, t_aae *aae);
void	pipe_error(t_cmd *cmds, t_aae *aae);
void	memory_error(t_cmd *cmds, t_aae *aae);
int		free_memory(t_cmd *cmds, t_aae *aae);
void	error_msg(int error, char *str, char *binary);

//	ft_memdel_bonus.c
void	*ft_memdel(char **ptr);

#endif
