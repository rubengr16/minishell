#include "executor.h"

void	mini_fprintf(char *str, char *message)
{
	ft_putstr_fd(str,  2);
	write(2, ": ", 2);
	ft_putstr_fd(message,  2);
	write(2, "\n", 1);
}

int	tmp_exist(void)
{
	int	fd;
	DIR	*tmp;

	tmp = opendir("/tmp");
	if (tmp)
	{
		fd = open("/tmp/HERE_DOC", O_RDWR | O_CREAT | O_TRUNC, 0644);
		closedir(tmp);
	}
	else
		fd = open("HERE_DOC", O_RDWR | O_CREAT | O_TRUNC, 0644);
	return (fd);
}

int	here_doc(t_redir *files)
{
	char	*str;
	int		fd;

	fd = tmp_exist();
	if (fd == -1)
		return (fd);
	write(2, "> ", 2);
	str = get_next_line(STDIN_FILENO);
	while (ft_strncmp(str, files->file, ft_strlen(files->file)) != 0)
	{
		ft_putstr_fd(str, fd);
		free(str);
		write(2, "> ", 2);
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
				mini_fprintf(files->file, "No such file or directory");
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
			mini_fprintf(files->file, "Permission denied");
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