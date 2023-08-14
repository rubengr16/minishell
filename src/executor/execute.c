/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:39:54 by rgallego          #+#    #+#             */
/*   Updated: 2023/08/14 12:30:25 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void piping(t_cmd *cmd, t_pipe *pipes, int i, int length)
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

static int exec_builtin(t_cmd *cmd)
{
	if (!cmd->cmd)
		return 0;
	if (!ft_strncmp(cmd->cmd, "echo", 5))
		ft_echo(cmd->args);
	else if (!ft_strncmp(cmd->cmd, "pwd", 4))
		ft_pwd();
	else if (!ft_strncmp(cmd->cmd, "export", 7))
		ft_export(cmd->args);
	else if (!ft_strncmp(cmd->cmd, "unset", 6))
		ft_unset(cmd->args);
	else if (!ft_strncmp(cmd->cmd, "env", 4))
		ft_env();
	else if (!ft_strncmp(cmd->cmd, "exit", 5))
		ft_exit(cmd->args);
	else if (!ft_strncmp(cmd->cmd, "cd", 3))
		ft_cd(cmd->args);
	else
		return (0);
	return (1);
}

static void exec_cmd(t_cmd *cmd, t_pipe *pipes, int i, int length)
{
	if (cmd->fd_in < 0 || cmd->fd_out < 0)
		exit(1);
	piping(cmd, pipes, i, length);
	dup2_and_close(cmd);
	if (!exec_builtin(cmd) && cmd->cmd)
	{
		cmd->cmd = verify_commands(ft_split(get_env("PATH"), ':'), cmd->cmd);
		if (cmd->cmd)
			execve(cmd->cmd, cmd->args, g_sigenv.envp);
		else
			exit(errno);
	}
	else if (is_builtin(cmd->cmd))
		exit(errno);
	exit(1);
}

static void	wait_status_change(t_cmd *cmd, pid_t last_id)
{
	pid_t	id;
	int		state;
	int		i;

	i = count_cmds(cmd);
	while (i)
	{
		id = wait(&state);
		if (id == last_id)
		{
			errno = state;
			if (WIFEXITED(errno))
				errno = WEXITSTATUS(errno);
		}
		i--;
	}
}

static void	prepare_command(t_cmd *cmd)
{
	t_cmd	*aux;
	t_pipe	*pipes;
	pid_t	id;
	int		i;

	pipes = malloc(sizeof(t_pipe) * count_cmds(cmd) - 1);
	aux = cmd;
	i = 0;
	while (aux)
	{
		if (i < (count_cmds(cmd) - 1))
			pipe(pipes[i]);
		id = fork();
		if (!id)
			exec_cmd(aux, pipes, i, count_cmds(cmd));
		if (i && (count_cmds(cmd) - 1))
			close(pipes[i - 1][PIPE_RD]);
		if (i < (count_cmds(cmd) - 1))
			close(pipes[i][PIPE_WR]);
		aux = aux->next;
		i++;
	}
	wait_status_change(cmd, id);
	free(pipes);
}

void	exec_main(t_cmd **cmd)
{
	int	builtin_on_parent;

	signal(SIGINT, sig_exec);
	signal(SIGQUIT, sig_exec);
	builtin_on_parent = is_builtin_on_parent(*cmd);
	files_management(*cmd, builtin_on_parent);
	if (builtin_on_parent && 0 <= (*cmd)->fd_in && 0 <= (*cmd)->fd_out)
		exec_builtin(*cmd);
	else
		prepare_command(*cmd);
	delete_cmd_list(cmd);
}
