#include "executtor.h"

int	exec_builtin(t_cmd *cmd, t_enviroment *env)
{
	if (ft_strncmp(cmd->cmd, "echo", 5) == 0)
		ft_echo(cmd->args);
	else if (ft_strncmp(cmd->cmd, "pwd", 4) == 0)
		ft_pwd();
	else if (ft_strncmp(cmd->cmd, "export", 7) == 0)
		ft_export(env, cmd->args);
	else if (ft_strncmp(cmd->cmd, "cd", 3) == 0)
		ft_cd(env, cmd->args);
	else if (ft_strncmp(cmd->cmd, "unset", 6) == 0)
		ft_unset(env, cmd->args);
	else if (ft_strncmp(cmd->cmd, "env", 4) == 0)
		ft_env(env);
	else
		return (0);
	return (1);
}

void	exec_command(t_cmd *aux, t_pipe *m_pipe, t_enviroment *env, char **path, int i, int length)
{
	int	j;

	if (i == 0 && aux->next){
		dup2(m_pipe[i][1], STDOUT_FILENO);
	}
	else if (i == length - 1 && length != 1){
		dup2(m_pipe[i - 1][0], STDIN_FILENO);
	}
	else if (length != 1)
	{
		dup2(m_pipe[i - 1][0], STDIN_FILENO);
		dup2(m_pipe[i][1], STDOUT_FILENO);
	}
	j = 0;
	while (j < length - 1)
	{
		close(m_pipe[j][0]);
		close(m_pipe[j++][1]);
	}
	if (!filesManagement(aux) && !exec_builtin(aux, env))
	{
		execve(verify_commands(path, aux->cmd), aux->args, NULL);
		exit(1);
	}
}

void	closeNwait(t_pipe *m_pipe, pid_t *id, int length)
{
	int	i;

	i = 0;
	while (i < length - 1)
	{
		close(m_pipe[i][0]);
		close(m_pipe[i++][1]);
	}
	i = 0;
	while (i < length)
		waitpid(id[i++], NULL, 0);
}

void	prepare_command(t_cmd *command, t_enviroment *env, char **path)
{
	t_cmd	*aux;
	int		i;
	t_pipe	*m_pipe;
	pid_t	*id;

	id = malloc(sizeof(pid_t) * count_commands(&command));
	m_pipe = malloc(sizeof(t_pipe) * count_commands(&command) - 1);
	aux = command;
	i = 0;
	while (i < count_commands(&command) - 1)
		pipe(m_pipe[i++]);
	i = 0;
	while (aux)
	{
		id[i] = fork();
		if (!id[i])
			exec_command(aux, m_pipe, env, path, i, count_commands(&command));
		aux = aux->next;
		i++;
	}
	closeNwait(m_pipe, id, count_commands(&command));
	free(id);
	free(m_pipe);
}

int	exec_main(t_cmd *command, t_enviroment *env)
{
	char	**path;
	int		i;

	i = 0;
	path = ft_split(get_env(env, "PATH"), ':');
	prepare_command(command, env, path);
	while (path[i])
		free(path[i++]);
	free(path);
	return (0);
}
