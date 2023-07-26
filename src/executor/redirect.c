/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:39:59 by rgallego          #+#    #+#             */
/*   Updated: 2023/07/26 16:14:51 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	mini_fprintf(char *str, char *message)
{
	ft_putstr_fd(str,  2);
	write(2, ": ", 2);
	ft_putstr_fd(message,  2);
	write(2, "\n", 1);
}

static char	*here_doc_expand_aux(char **line, unsigned int name_len,
	unsigned int *i)
{
	char	*name;
	char	*vble;

	if (!name_len)
		return (vble_cpy(line, "$", i, 0));
	name = malloc(sizeof(char) * (name_len + 1));
	if (!name)
		*line = mini_error(NULL, NULL, ALLOC_ERR, *line);
	ft_strlcpy(name, &((*line)[*i]), name_len + 1);
	vble = get_env(name);
	free(name);
	if (!vble)
		return (vble_cpy(line, "", i, name_len));
	return (vble_cpy(line, vble, i, name_len));
}

static char	*here_doc_expand(char **line)
{
	unsigned int	name_len;
	unsigned int	i;

	if (!*line)
		return (NULL);
	i = 0;
	while (*line && (*line)[i])
	{
		if ((*line)[i] == '$')
		{
			i++;
			name_len = 0;
			while ((*line)[i + name_len] && (*line)[i + name_len] != '\''
				&& (*line)[i + name_len] != '\"' && (*line)[i + name_len] != '\n'
				&& (*line)[i + name_len] != ' ')
				name_len++;
			*line = here_doc_expand_aux(line, name_len, &i);
		}
		i++;
	}
	return (*line);
}

static int	here_doc(t_redir *files)
{
	int		here_pipe[2];
	char	*str;
	char	*aux;

	if (pipe(here_pipe) == -1)
		return (-1);
	write(2, "> ", 2);
	str = ft_strdup("");
	aux = get_next_line(STDIN_FILENO);
	while (ft_strncmp(aux, files->file, ft_strlen(files->file) + 1) != '\n')
	{
		aux = here_doc_expand(&aux);
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

static int	redirect_in(t_cmd *cmd, int close_all)
{
	t_redir	*redir;
	int		fd_in;

	redir = cmd->r_in;
	while (redir)
	{
		if (redir->type == R_IN_HERE_DOC)
			fd_in = here_doc(redir);
		else
		{
			fd_in = open(cmd->r_in->file, O_RDONLY);
			if (fd_in < 0)
				perror(redir->file);
		}
		if (close_all)
			dup2(fd_in, STDIN_FILENO);
		close(fd_in);
		redir = redir->next;
	}
	return (0);
}

static int	redirect_out(t_cmd *cmd, int close_all)
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
			perror(redir->file);
		if (close_all)
			dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
		redir = redir->next;
	}
	return (0);
}

int	files_management(t_cmd *cmd, int close_all)
{
	t_cmd	*aux;
	int		result;

	aux = cmd;
	while (cmd && cmd->fd_in && cmd->fd_out)
	{
		if (cmd->r_in)
			redirect_in(cmd, close_all);
		if (cmd->r_out)
			redirect_out(cmd, close_all);
		aux = aux->next;
	}
}
