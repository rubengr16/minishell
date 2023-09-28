/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:39:54 by rgallego          #+#    #+#             */
/*   Updated: 2023/09/07 18:14:21 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	exec_builtin(t_cmd *cmd, int is_child)
{
	if (!cmd->cmd)
		return (0);
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
		ft_exit(cmd->args, is_child);
	else if (!ft_strncmp(cmd->cmd, "cd", 3))
		ft_cd(cmd->args);
	else
		return (0);
	return (1);
}

static void	exec_cmd(t_cmd *cmd, t_pipe *pipes, int i, int length)
{
	char	*path;

	if (cmd->fd_in < 0 || cmd->fd_out < 0)
		exit(1);
	piping(cmd, pipes, i, length);
	dup2_and_close(cmd);
	if (!cmd->cmd || !ft_strncmp(cmd->cmd, "", 1))
		exit(0);
	if (!exec_builtin(cmd, 1))
	{
		path = get_env("PATH");
		cmd->cmd = verify_command(ft_split(path, ':'), cmd->cmd);
		if (path)
			free(path);
		if (cmd->cmd)
			execve(cmd->cmd, cmd->args, g_sigenv.envp);
		else
			exit(g_sigenv.our_errno);
	}
	else if (is_builtin(cmd->cmd))
		exit(g_sigenv.our_errno);
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
		if (id == last_id && g_sigenv.signal == 0)
		{
			g_sigenv.our_errno = state;
			if (WIFEXITED(g_sigenv.our_errno))
				g_sigenv.our_errno = WEXITSTATUS(g_sigenv.our_errno);
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
			if (pipe(pipes[i]))
				return ((void)mini_error(NULL, NULL, SYS_ERR, NULL));
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
		exec_builtin(*cmd, 0);
	else
		prepare_command(*cmd);
	delete_cmd_list(cmd);
}
