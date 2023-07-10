#include "executtor.h"

void	exec_command(t_cmd *command, char **path)
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
		{
			if (i == 0 && aux->next)
				dup2(m_pipe[i][1], STDOUT_FILENO);
			else if (i == count_commands(&command) - 1 && !aux->next)
				dup2(m_pipe[i - 1][0], STDIN_FILENO);
			close(m_pipe[0][0]);
			close(m_pipe[0][1]);
			execve(verify_commands(path, aux->cmd), aux->args, NULL);
			exit(1);
		}
		aux = aux->next;
		i++;
	}
	i = 0;
	close(m_pipe[0][0]);
	close(m_pipe[0][1]);
	while (i < count_commands(&command))
		waitpid(id[i++], NULL, 0);
	free(id);
	free(m_pipe);
}

int	exec_main(t_cmd *command, t_enviroment *env)
{
	char	**path;
	int		i;

	i = 0;
	path = ft_split(get_env(env, "PATH"), ':');
	exec_command(command, path);
	while (path[i])
		free(path[i++]);
	free(path);
	return (0);
}
