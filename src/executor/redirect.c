/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:39:59 by rgallego          #+#    #+#             */
/*   Updated: 2023/08/15 16:54:09 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	piping(t_cmd *cmd, t_pipe *pipes, int i, int length)
{
	if (i == 0 && cmd->next)
	{
		close(pipes[i][PIPE_RD]);
		dup2(pipes[i][PIPE_WR], STDOUT_FILENO);
		close(pipes[i][PIPE_WR]);
	}
	else if (i < (length - 1) && 1 < length)
	{
		close(pipes[i][PIPE_RD]);
		dup2(pipes[i - 1][PIPE_RD], STDIN_FILENO);
		close(pipes[i - 1][PIPE_RD]);
		dup2(pipes[i][PIPE_WR], STDOUT_FILENO);
		close(pipes[i][PIPE_WR]);
	}
	else if (1 < length)
	{
		dup2(pipes[i - 1][PIPE_RD], STDIN_FILENO);
		close(pipes[i - 1][PIPE_RD]);
	}
}

void	dup2_and_close(t_cmd *cmd)
{
	if (cmd->fd_in != STDIN_FILENO)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		close(cmd->fd_in);
	}
	if (cmd->fd_out != STDOUT_FILENO)
	{
		dup2(cmd->fd_out, STDOUT_FILENO);
		close(cmd->fd_out);
	}
}

static void	redirect_in(t_cmd *cmd, t_redir redir,	int close_all)
{
	if (redir.type == R_IN_HERE_DOC)
	{
		signal(SIGINT, sig_here_doc);
		signal(SIGQUIT, SIG_IGN);
		cmd->fd_in = here_doc(redir.file);
	}
	else
	{
		cmd->fd_in = open(redir.file, O_RDONLY, 0222);
		if (cmd->fd_in < 0)
			perror(redir.file);
		else if (!is_last_redir(redir.next, R_IN, R_IN_HERE_DOC) || close_all)
			close(cmd->fd_in);
	}
}

static void	redirect_out(t_cmd *cmd, t_redir redir,	int close_all)
{
	if (redir.type == R_OUT_APPEND)
		cmd->fd_out = open(redir.file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		cmd->fd_out = open(redir.file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd->fd_out < 0)
		perror(redir.file);
	else if (!is_last_redir(redir.next, R_OUT, R_OUT_APPEND) || close_all)
		close(cmd->fd_out);
}

void	files_management(t_cmd *cmd, int close_all)
{
	t_cmd	*cmd_aux;
	t_redir	*redir_aux;

	cmd_aux = cmd;
	while (cmd_aux && 0 <= cmd_aux->fd_in && 0 <= cmd_aux->fd_out)
	{
		redir_aux = cmd_aux->redir;
		while (redir_aux && 0 <= cmd_aux->fd_in && 0 <= cmd_aux->fd_out)
		{
			if (redir_aux->type == R_IN || redir_aux->type == R_IN_HERE_DOC)
				redirect_in(cmd_aux, *redir_aux, close_all);
			if (redir_aux->type == R_OUT || redir_aux->type == R_OUT_APPEND)
				redirect_out(cmd_aux, *redir_aux, close_all);
			if (0 <= cmd_aux->fd_in && 0 <= cmd_aux->fd_out)
				redir_aux = redir_aux->next;
		}
		cmd_aux = cmd_aux->next;
	}
}
