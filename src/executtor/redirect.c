#include "executtor.h"

int	here_doc(t_redir *files)
{
	char	*str;
	char	*buffer;

	str = get_next_line(STDIN_FILENO);
	while (ft_strncmp(str, files->file, ft_strlen(files->file)) != 0)
	{
		ft_putstr_fd(str, fd);
		free(str);
		str = get_next_line(STDIN_FILENO);
	}
	free(str);
	return (fd);
}

int	redirect_in(t_cmd *cmd)
{
	t_redir	*files;
	int		fd_in;

	files = cmd->r_in;
	while (files)
	{
		if (files->type == R_IN_HERE_DOC)
		{
			fd_in = here_doc(files);
			dup2(fd_in, STDIN_FILENO);
			close(fd_in);
		}
		else
		{
			if (access(cmd->r_in->file, R_OK) == 0)
			{
				fd_in = open(cmd->r_in->file, O_RDONLY);
				dup2(fd_in, STDIN_FILENO);
				close(fd_in);
			}
			else
			{
				printf("%s: Error. El fichero no existe o no tienes permisos\n", files->file);
				return (1);
			}
		}
		files = files->next;
	}
	return (0);
}

int	redirect_out(t_cmd *cmd)
{
	t_redir	*files;
	int		fd_out;

	files = cmd->r_out;
	while (files)
	{
		if (access(files->file, F_OK) == 0 && access(files->file, W_OK) == -1){
			printf("%s: Error. No tienes permisos para escribir en el fichero\n", files->file);
			return (1);
		}
		unlink(files->file);
		if (files->type == R_OUT_APPEND)
			fd_out = open(files->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd_out = open(files->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
		files = files->next;
	}
	return (0);
}

int	filesManagement(t_cmd *cmd)
{
	int	result;

	result = 0;
	if (cmd->r_in)
		result = redirect_in(cmd);
	if (cmd->r_out)
		result = redirect_out(cmd);
	return (result);
}
