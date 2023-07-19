#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include <dirent.h>
# include "enviroment.h"
# include "lexer.h"

/***************************** PIPE MANAGEMENT ****************************** */
# define PIPE_RD 0
# define PIPE_WR 1

int		exec_main(t_cmd *command, t_enviroment *env);
char	*verify_commands(char **path, char *cmd);
int		count_cmds(t_cmd *cmd);
int		files_management(t_cmd *cmd);
void	mini_fprintf(char *str, char *message);
typedef	int t_pipe [2];

#endif
