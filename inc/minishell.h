#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>
# include <dirent.h>
# include <stdlib.h>
# include <stdio.h>
# include "libft.h"

// Lista

typedef struct s_node
{

}t_node;


// Arbol

typedef struct s_redirect
{
	struct s_pipe right;
	struct s_redirect left;
}t_redirect;

typedef struct s_cmd
{
	struct s_pipe right;
	struct s_redirect left;
}t_cmd;

typedef struct s_pipe
{
	struct s_pipe right;
	struct s_cmd left;
}t_pipe;

// Ha venido ya mi hermano, so...

#endif