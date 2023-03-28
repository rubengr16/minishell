/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 19:24:05 by rgallego          #+#    #+#             */
/*   Updated: 2022/09/23 18:58:45 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/******************************** LIBRARIES ********************************* */
# include <sys/wait.h>		/***	pid_t	wait(int *wsatus);	***/
# include <stdio.h>		/***	void	perror(const char *s);	***/
# include <errno.h>
# include <unistd.h>	/***	int		dup2(int oldfd, int newfd);
						  		pid_t	fork(void);
						  		int 	pipe(int pipefd[2]);	***/
# include <stdlib.h>
# include <fcntl.h>		/***	int		open(const char *path, int oflag, ...);
								***/
# include "libft.h"
# include "get_next_line.h"
# include "cmdlist.h"
# include "pipelist.h"

/**************************** ERROR MANAGEMENT ****************************** */
# define ERR_DUP2 -1
# define ERR_ARGC 2
# define ERR_ENVP 3
# define ERR_CMD 4

/***************************** PIPE MANAGEMENT ****************************** */
# define PIPE_RD 0
# define PIPE_WR 1

/******************************** HERE_DOC ********************************** */
# define HERE_DOC "here_doc"
# define PATH_DOC "/tmp/here_doc"

/******************************* STRUCTURE ********************************** */
typedef struct s_pipex
{
	int			fdin;
	int			fdout;
	char		*limiter;
	t_cmdlist	*cmds;
	t_pipelist	*pipes;
}	t_pipex;

/********************************* UTILS ************************************ */
void	error_msg(t_pipex pipex, char *str, int error);
void	preparate_pipex(t_pipex *pipex, char **argv);
char	*ft_strjoinsep(char const *s1, char const *s2, char *c);

/********************************* PIPEX ************************************ */
void	arevalidcmds(t_pipex pipex, char **envp);
void	executor(t_pipex pipex, char **envp, int n_cmds);

#endif
