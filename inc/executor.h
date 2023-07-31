/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:40:07 by rgallego          #+#    #+#             */
/*   Updated: 2023/07/31 09:00:13 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include <dirent.h>
# include "enviroment.h"
# include "builtins.h"
# include "lexer.h"

/********************************** PIPE ************************************ */
typedef	int t_pipe [2];

/***************************** PIPE MANAGEMENT ****************************** */
# define PIPE_RD 0
# define PIPE_WR 1

/********************************* EXECUTOR ********************************* */
void		exec_main(t_cmd **command);

/********************************* REDIRECT ********************************* */
void	mini_fprintf(char *str, char *message);
void	dup2_and_close(t_cmd *cmd);
void	files_management(t_cmd *cmd, int need_dup2);

/*********************************** UTILS ********************************** */
int		count_cmds(t_cmd *cmd);
int		is_builtin(char *cmd);
int		is_builtin_on_parent(t_cmd	*cmd);
char	*verify_commands(char **path, char *cmd);

#endif
