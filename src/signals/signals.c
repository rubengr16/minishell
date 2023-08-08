#include "signals.h"

void	sigNormal(int sig)
{
	if (sig == SIGINT){
		free(g_sigenv.last_status);
		g_sigenv.last_status = ft_strdup("1");
		write(2, "\r\nminishell> ", 13);
	}
	else if (sig == SIGQUIT)
		write(1, "", 0);
}

void	sigExec(int sig)
{
	if (sig == SIGINT){
		free(g_sigenv.last_status);
		g_sigenv.last_status = ft_strdup("130");
		write(2, "\n", 1);
	}
	else if (sig == SIGQUIT)
		write(1, "", 0);
}
