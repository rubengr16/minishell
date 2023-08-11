#include "signals.h"

void	sig_normal(int sig)
{
	if (sig == SIGINT)
	{
		write(2, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
	}
	else if (sig == SIGQUIT)
	{
		write(2, "\b\b", 2);
	}
}

void	sig_exec(int sig)
{
	if (sig == SIGINT)
	{
		write(2, "\n", 1);
	}
	else if (sig == SIGQUIT)
		write(2, "Quit: 3\n", 8);
}
