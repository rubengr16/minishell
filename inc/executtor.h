#ifndef EXECUTTOR_H
# define EXECUTTOR_H

# include <sys/wait.h>
# include <errno.h>
# include <dirent.h>
# include "enviroment.h"

int		exec_main(t_cmd *command, t_enviroment *env);
char	*verify_commands(char **path, char *cmd);
int		count_commands(t_cmd **cmd);
int		filesManagement(t_cmd *cmd);
void	mini_fprintf(char *str, char *message);
typedef	int t_pipe [2];

#endif