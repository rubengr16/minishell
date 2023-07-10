#ifndef EXECUTTOR_H
# define EXECUTTOR_H

# include <sys/wait.h>
# include "enviroment.h"

int		exec_main(t_cmd *command, t_enviroment *env);
char	*verify_commands(char **path, char *cmd);
int		count_commands(t_cmd **cmd);

typedef	int t_pipe [2];

#endif