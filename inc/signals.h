#ifndef SIGNALS_H
# define SIGNALS_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "enviroment.h"

void	sig_normal(int sig);
void	sig_exec(int sig);
void	sig_here_doc(int sig);

#endif
