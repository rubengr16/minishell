#include "executor.h"

int	exec_builtin(t_cmd *cmd, char **env)
{
	if (ft_strncmp(cmd->cmd, "echo", 5) == 0)
		ft_echo(cmd->args);
	else if (ft_strncmp(cmd->cmd, "pwd", 4) == 0)
		ft_pwd();
	else if (ft_strncmp(cmd->cmd, "export", 7) == 0)
		ft_export(env, cmd->args);
	else if (ft_strncmp(cmd->cmd, "unset", 6) == 0)
		ft_unset(env, cmd->args);
	else if (ft_strncmp(cmd->cmd, "env", 4) == 0)
		ft_env(env);
	else
		return (0);
	return (1);
}

int	exec_cmd(t_cmd *aux, t_pipe *pipe, char **my_envp, int i, int length)
{
	char **path;

	path = ft_split(get_env(my_envp, "PATH"), ':');
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
	if (!files_management(aux) && !exec_builtin(aux, my_envp))
	{
		execve(verify_commands(path, aux->cmd), aux->args, my_envp);
		mini_fprintf(aux->cmd, "command not found");
		exit(1);
	}
	while (path[i])
		free(path[i++]);
	free(path);
	exit(1);
}

void	prepare_command(t_cmd *command, char **env)
{
	t_cmd	*aux;
	t_pipe	*pipes;
	pid_t	*ids;
	int		state;
	int		i;

	ids = malloc(sizeof(pid_t) * count_cmds(command));
	pipes = malloc(sizeof(t_pipe) * count_cmds(command) - 1);
	aux = command;
	i = 0;
	state = 0;
	while (aux && 0 <= state)
	{
		if (i < (count_cmds(command) - 1))
			pipe(pipes[i]);
		ids[i] = fork();
		if (!ids[i])
			state = exec_cmd(aux, pipes, env, i, count_cmds(command));
		if (i && (count_cmds(command) - 1))
			close(pipes[i - 1][PIPE_RD]);
		if (i < (count_cmds(command) - 1))
			close(pipes[i][PIPE_WR]);
		aux = aux->next;
		i++;
	}
	int length = count_cmds(command);
	while (length--)
		wait(NULL);
	free(ids);
	free(pipes);
}

/*
 * if there are 2 or more cmds, manages the files openings either if there
 * is here_doc or not.
 * INPUT:	t_cmd *cmd
 * OUTPUT:	void
 */
// static void	files_mngment(t_cmd *cmd)
// {
// 	t_redir	*aux;

// 	aux = cmd->r_in;
// 	while (aux)
// 		if (aux->type == R_IN_HERE_DOC)
// 			read_from_stdin(pipex, fin);
// 	pipex->fdin = open(fin, O_RDONLY);
// 	if (pipex->limiter)
// 		pipex->fdout = open(fout, O_WRONLY | O_CREAT | O_APPEND, 0644);
// 	else
// 		pipex->fdout = open(fout, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (pipex->fdin < 0)
// 		error_msg(*pipex, fin, ERR_SYS);
// 	if (pipex->fdout < 0)
// 		error_msg(*pipex, fout, ERR_SYS);
// }

int	exec_main(t_cmd *command, char **env)
{
	if (ft_strncmp(command->cmd, "exit", 5) == 0)
		exit(0);
	if (ft_strncmp(command->cmd, "cd", 3) == 0)
	{
		ft_cd(env, command->args);
		return (0);
	}
	prepare_command(command, env);
	return (0);
}
