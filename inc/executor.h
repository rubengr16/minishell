/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: socana-b <socana-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:40:07 by rgallego          #+#    #+#             */
/*   Updated: 2023/08/02 18:20:49 by socana-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <sys/wait.h>
# include <fcntl.h>
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
