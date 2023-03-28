/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 02:23:00 by rgallego          #+#    #+#             */
/*   Updated: 2022/09/23 19:01:46 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	pipex.fdin = -1;
	pipex.fdout = -1;
	pipex.limiter = NULL;
	pipex.cmds = NULL;
	pipex.pipes = NULL;
	if (argc < 5)
		error_msg(pipex, NULL, ERR_ARGC);
	preparate_pipex(&pipex, argv);
	arevalidcmds(pipex, envp);
	pipex.pipes = pipelistinitpush(pipex.cmds->n_elem - 1);
	if (!pipex.pipes)
		error_msg(pipex, "pipelistinitpush failed", ERR_SYS);
	executor(pipex, envp, pipex.cmds->n_elem);
	cmdlistdelall(pipex.cmds);
	pipelistdelall(pipex.pipes);
	return (0);
}
