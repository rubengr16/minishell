/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:40:07 by rgallego          #+#    #+#             */
/*   Updated: 2023/07/24 00:39:04 by rgallego         ###   ########.fr       */
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
int		exec_main(t_cmd *command, char ***env);

/********************************* REDIRECT ********************************* */
void	mini_fprintf(char *str, char *message);
int		files_management(t_cmd *cmd);

/*********************************** UTILS ********************************** */
int		count_cmds(t_cmd *cmd);
int		is_builtin(char *cmd);
int		count_builtins(t_cmd *cmd_list);
char	*verify_commands(char **path, char *cmd);

#endif
