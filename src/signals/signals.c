/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 12:43:12 by rgallego          #+#    #+#             */
/*   Updated: 2023/09/07 18:14:29 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

void	sig_normal(int sig)
{
	if (sig == SIGINT)
	{
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		g_sigenv.our_errno = 1;
	}
	g_sigenv.signal = sig;
}

void	sig_exec(int sig)
{
	if (sig == SIGINT)
	{
		write(2, "\n", 1);
		g_sigenv.our_errno = 130;
	}
	else if (sig == SIGQUIT)
	{
		write(2, "Quit: ", 6);
		ft_putnbr_fd(sig, STDERR_FILENO);
		write(2, "\n", 1);
		g_sigenv.our_errno = 131;
	}
	g_sigenv.signal = sig;
}

void	sig_here_doc(int sig)
{
	if (sig == SIGINT)
	{
		write(2, "\n", 1);
		g_sigenv.our_errno = 1;
	}
	g_sigenv.signal = sig;
}
