/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_mgment.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 18:18:21 by rgallego          #+#    #+#             */
/*   Updated: 2022/09/23 19:02:19 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
 * receives pipex to close the fds before exiting, str for a custom message and
 * an error code for knowing how to print the chosen message in order to inform
 * the user about the error.
 * INPUT:	t_pipex *pipex, char *str, int error
 * OUTPUT:	void
 */
void	error_msg(t_pipex pipex, char *str, int error)
{
	if (error == ERR_ARGC)
	{
		ft_putstr_fd("Please, enter 4 ", STDERR_FILENO);
		ft_putendl_fd("or more arguments with the structure:", STDERR_FILENO);
		ft_putendl_fd("./pipex <f1> <cmd1> <cmd2> [...] <f2>", STDERR_FILENO);
		ft_putstr_fd("or\n./pipex here_doc ", STDERR_FILENO);
		ft_putendl_fd("LIMITER <cmd1> <cmd2> [...] <f2>", STDERR_FILENO);
	}
	else if (error == ERR_ENVP)
		ft_putendl_fd(str, STDERR_FILENO);
	else if (error == ERR_SYS || error == ERR_CMD)
		perror(str);
	if (pipex.fdin >= 0)
		close(pipex.fdin);
	if (pipex.fdout >= 0)
		close(pipex.fdout);
	exit(errno);
}
