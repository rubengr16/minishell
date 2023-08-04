/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:39:59 by rgallego          #+#    #+#             */
/*   Updated: 2023/08/05 01:37:36 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	dup2_and_close(t_cmd *cmd)
{
	if (cmd->fd_in != STDIN_FILENO)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		close(cmd->fd_in);
	}
	if (cmd->fd_out != STDOUT_FILENO)
	{
		dup2(cmd->fd_out, STDOUT_FILENO);
		close(cmd->fd_out);
	}
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
		*line = mini_error(NULL, NULL, SYS_ERR, *line);
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

static int	here_doc(char *end_of_input)
{
	int		here_pipe[2];
	char	*str;
	char	*aux;

	if (pipe(here_pipe) == -1)
		return (-1);
	write(2, "> ", 2);
	str = ft_strdup("");
	aux = get_next_line(STDIN_FILENO);
	while (ft_strncmp(aux, end_of_input, ft_strlen(end_of_input) + 1) != '\n')
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

static void	redirect_in(t_cmd *cmd, t_redir redir,	int close_all)
{
	if (redir.type == R_IN_HERE_DOC)
		cmd->fd_in = here_doc(redir.file);
	else
	{
		cmd->fd_in = open(redir.file, O_RDONLY, 0222);
		if (cmd->fd_in < 0)
			perror(redir.file);
		else if (redir.next || close_all)
			close(cmd->fd_in);
	}
}

static void	redirect_out(t_cmd *cmd, t_redir redir,	int close_all)
{
	if (redir.type == R_OUT_APPEND)
		cmd->fd_out = open(redir.file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		cmd->fd_out = open(redir.file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd->fd_out < 0)
		perror(redir.file);
	else if (redir.next || close_all)
		close(cmd->fd_out);
}

void	files_management(t_cmd *cmd, int close_all)
{
	t_cmd	*cmd_aux;
	t_redir	*redir_aux;

	cmd_aux = cmd;
	while (cmd_aux && 0 <= cmd_aux->fd_in && 0 <= cmd_aux->fd_out)
	{
		redir_aux = cmd_aux->redir;
		while (redir_aux && 0 <= cmd_aux->fd_in && 0 <= cmd_aux->fd_out)
		{
			if (redir_aux->type == R_IN || redir_aux->type == R_IN_HERE_DOC)
				redirect_in(cmd_aux, *redir_aux, close_all);
			if (redir_aux->type == R_OUT || redir_aux->type == R_OUT_APPEND)
				redirect_out(cmd_aux, *redir_aux, close_all);
			if (0 <= cmd_aux->fd_in && 0 <= cmd_aux->fd_out)
				redir_aux = redir_aux->next;
		}
		cmd_aux = cmd_aux->next;
	}
}
