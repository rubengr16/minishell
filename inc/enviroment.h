#ifndef ENVIROMENT_H
# define ENVIROMENT_H

# include "lexer.h"
# include "utils.h"
# include <stdio.h>
# include <signal.h>

/* ***************************** ENVIROMENT ****************************** */

char	**create_my_env(char **envp);
void	delete_env_vbles(char ***my_envp);
char	*get_env(char **my_envp, char *name);
// void	mini_split(char *variable, t_variable *new_var);

/* ***************************** BUILTINS ****************************** */

void	ft_echo(char **args);							// 3 Done it
void	ft_cd(char **my_envp, char **args);		// 3 Done it
void	ft_pwd(void);									// 3 Done it
void	ft_export(char ***my_env, char **args);	// 2 Checking
void	ft_unset(char ***my_env, char **args);	// 3 Done it
void	ft_env(char **my_envp);					// 3 Done it

/* ***************************** UTILS ****************************** */
char	*cd_aux(char **my_envp, char **args, int *free_flag);

#endif
