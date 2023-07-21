#include "executor.h"

void	mini_fprintf(char *str, char *message)
{
	ft_putstr_fd(str,  2);
	write(2, ": ", 2);
	ft_putstr_fd(message,  2);
	write(2, "\n", 1);
}

int	here_doc(t_redir *files)
{
	int		here_pipe[2];
	char	*str;
	char	*aux;

	if (pipe(here_pipe) == -1)
		return (-1);
	write(2, "> ", 2);
	str = ft_strdup("");
	aux = get_next_line(STDIN_FILENO);
	while (ft_strncmp(aux, files->file, ft_strlen(files->file)))
	{
		str = ft_strjoin(str, aux);
		free(aux);
		write(2, "> ", 2);
		aux = get_next_line(STDIN_FILENO);
	}
	free(aux);
	write(here_pipe[PIPE_WR], str, ft_strlen(str));
	close(here_pipe[PIPE_WR]);
	return (here_pipe[PIPE_RD]);
}

int	redirect_in(t_cmd *cmd)
{
	t_redir	*redir;
	int		fd_in;

	redir = cmd->r_in;
	while (redir)
	{
		if (redir->type == R_IN_HERE_DOC)
		{
			fd_in = here_doc(redir);
			dup2(fd_in, STDIN_FILENO);
			close(fd_in);
		}
		else
		{
			fd_in = open(cmd->r_in->file, O_RDONLY);
			if (fd_in < 0)
			{
				mini_fprintf(redir->file, "No such file or directory");
				return (1);
			}
			dup2(fd_in, STDIN_FILENO);
			close(fd_in);
		}
		redir = redir->next;
	}
	return (0);
}

int	redirect_out(t_cmd *cmd)
{
	t_redir	*redir;
	int		fd_out;

	redir = cmd->r_out;
	while (redir)
	{
		if (redir->type == R_OUT_APPEND)
			fd_out = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd_out = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_out < 0)
		{
			mini_fprintf(redir->file, "Permission denied");
			return (1);
		}
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
		redir = redir->next;
	}
	return (0);
}

int	files_management(t_cmd *cmd)
{
	int	result;

	result = 0;
	if (cmd->r_in)
		result = redirect_in(cmd);
	if (cmd->r_out)
		result = redirect_out(cmd);
	return (result);
}
