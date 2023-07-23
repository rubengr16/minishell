/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:39:54 by rgallego          #+#    #+#             */
/*   Updated: 2023/07/24 00:49:44 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	exec_builtin(t_cmd *cmd, char ***my_envp)
{
	if (!ft_strncmp(cmd->cmd, "echo", 5))
		ft_echo(cmd->args);
	else if (!ft_strncmp(cmd->cmd, "pwd", 4))
		ft_pwd();
	else if (!ft_strncmp(cmd->cmd, "export", 7))
		ft_export(my_envp, cmd->args);
	else if (!ft_strncmp(cmd->cmd, "unset", 6))
	{
		printf("UNSETTTTTTTT\n");
		ft_unset(my_envp, cmd->args);
	}
	else if (!ft_strncmp(cmd->cmd, "env", 4))
		ft_env(*my_envp);
	else if (!ft_strncmp(cmd->cmd, "exit", 5))
		exit(0);
	else if (!ft_strncmp(cmd->cmd, "cd", 3))
		ft_cd(*my_envp, cmd->args);
	else
		return (0);
	return (1);
}

static int	exec_cmd(t_cmd *aux, t_pipe *pipe, char ***my_envp, int i,
	int length)
{
	char **path;

	path = ft_split(get_env(*my_envp, "PATH"), ':');
	if (i == 0 && aux->next)
	{
		close(pipe[i][PIPE_RD]);
		dup2(pipe[i][PIPE_WR], STDOUT_FILENO);
		close(pipe[i][PIPE_WR]);
	}
	else if (i < (length - 1) && 1 < length)
	{
		close(pipe[i][PIPE_RD]);
		dup2(pipe[i - 1][PIPE_RD], STDIN_FILENO);
		close(pipe[i - 1][PIPE_RD]);
		dup2(pipe[i][PIPE_WR], STDOUT_FILENO);
		close(pipe[i][PIPE_WR]);
	}
	else if (1 < length)
	{
		dup2(pipe[i - 1][PIPE_RD], STDIN_FILENO);
		close(pipe[i - 1][PIPE_RD]);
	}
	if (!files_management(aux))
	{
		execve(verify_commands(path, aux->cmd), aux->args, *my_envp);
		mini_fprintf(aux->cmd, "command not found");
		exit(1);
	}
	while (path[i])
		free(path[i++]);
	free(path);
	exit(1);
}

static void	prepare_command(t_cmd *command, char ***my_envp)
{
	t_cmd	*aux;
	t_pipe	*pipes;
	int		state;
	int		i;

	pipes = malloc(sizeof(t_pipe) * count_cmds(command) - 1);
	aux = command;
	i = 0;
	state = 0;
	while (aux && 0 <= state)
	{
		if (i < (count_cmds(command) - 1))
			pipe(pipes[i]);
		if (!exec_builtin(aux, my_envp) && !fork())
			state = exec_cmd(aux, pipes, my_envp, i, count_cmds(command));
		if (i && (count_cmds(command) - 1))
			close(pipes[i - 1][PIPE_RD]);
		if (i < (count_cmds(command) - 1))
			close(pipes[i][PIPE_WR]);
		aux = aux->next;
		i++;
	}
	int length = count_cmds(command) - count_builtins(command);
	while (length--)
		wait(NULL);
	free(pipes);
}

int	exec_main(t_cmd *command, char ***my_envp)
{
	prepare_command(command, my_envp);
	return (0);
}
