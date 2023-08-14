/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 12:43:12 by rgallego          #+#    #+#             */
/*   Updated: 2023/08/14 12:43:15 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include <sys/ioctl.h>

void	sig_normal(int sig)
{
	if (sig == SIGINT)
	{
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

void	sig_exec(int sig)
{
	if (sig == SIGINT)
		write(2, "\n", 1);
	else if (sig == SIGQUIT)
		write(2, "Quit: 3\n", 8);
}

void	sig_here_doc(int sig)
{
	if (sig == SIGINT)
		write(2, "\n", 1);
	else if (sig == SIGQUIT)
		ioctl(STDIN_FILENO, TIOCSTI, "\b\b");
}
