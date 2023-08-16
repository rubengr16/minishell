/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:40:07 by rgallego          #+#    #+#             */
/*   Updated: 2023/08/16 13:12:24 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <sys/wait.h>
# include <fcntl.h>
# include <dirent.h>
# include <stdio.h>
# include "utils.h"
# include "signals.h"
# include "builtins.h"
# include "lexer.h"

# define ERR_DUP2 -1
# define NOT_FOUND 1
# define OK 0
# define EXEC_DENIED -1

/********************************** PIPE ************************************ */
typedef int	t_pipe [2];

/***************************** PIPE MANAGEMENT ****************************** */
# define PIPE_RD 0
# define PIPE_WR 1

/********************************* EXECUTOR ********************************* */
void	exec_main(t_cmd **command);

/********************************* REDIRECT ********************************* */
void	dup2_and_close(t_cmd *cmd);
void	files_management(t_cmd *cmd, int need_dup2);
void	piping(t_cmd *cmd, t_pipe *pipes, int i, int length);

/******************************* REDIR_UTILS ******************************** */
int		here_doc(char *end_of_input);
int		is_last_redir(t_redir *next, enum e_token_type type1,
			enum e_token_type type2);

/*********************************** UTILS ********************************** */
int		count_cmds(t_cmd *cmd);
int		is_builtin(char *cmd);
int		is_builtin_on_parent(t_cmd	*cmd);
char	*verify_commands(char **path, char *cmd);

#endif
