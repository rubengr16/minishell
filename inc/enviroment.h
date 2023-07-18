#ifndef ENVIROMENT_H
# define ENVIROMENT_H

# include "lexer.h"
# include <stdio.h>
# include <signal.h>

typedef struct s_variable
{
	char				*name;
	char				*value;
	struct s_variable	*next;
}t_variable;

typedef struct s_enviroment
{
	t_variable	*head;
	t_variable	*tail;
}t_enviroment;

/* ***************************** ENVIROMENT ****************************** */

int		create_env_list(char **envp, t_enviroment *my_env);
void	delete_env_variables(t_enviroment *my_env);
void	mini_split(char *variable, t_variable *new_var);
char	*get_env(t_enviroment *my_env, char *name);

/* ***************************** BUILTINS ****************************** */

void	ft_echo(char **args);							// 3 Done it
void	ft_cd(t_enviroment *my_env, char **args);		// 3 Done it
void	ft_pwd(void);									// 3 Done it
void	ft_export(t_enviroment *my_env, char **args);	// 2 Checking
void	ft_unset(t_enviroment *my_env, char **args);	// 3 Done it
void	ft_env(t_enviroment *my_env);					// 3 Done it

/* ***************************** UTILS ****************************** */

int		is_equals(char *name, char **args);
void	delete_node(t_variable *node);
char	*cd_aux(t_enviroment *my_env, char **args, int *free_flag);
int		check_splitable(char *str);

#endif