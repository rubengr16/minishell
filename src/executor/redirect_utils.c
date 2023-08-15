/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 11:16:05 by socana-b          #+#    #+#             */
/*   Updated: 2023/08/15 16:49:47 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static char	*here_doc_expand_aux(char **line, unsigned int name_len,
	unsigned int *i)
{
	char	*name;
	char	*vble;
	char	*expansion_result;

	if (!name_len)
		return (vble_cpy(line, "$", i, 0));
	name = malloc(sizeof(char) * (name_len + 1));
	if (!name)
		*line = mini_error(NULL, NULL, SYS_ERR, *line);
	ft_strlcpy(name, &((*line)[*i]), name_len + 1);
	vble = get_env(name);
	if (!vble)
		expansion_result = vble_cpy(line, "", i, name_len);
	expansion_result = vble_cpy(line, vble, i, name_len);
	if (vble && !ft_strncmp(name, "?", 1))
		free(vble);
	free(name);
	return (expansion_result);
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
				&& (*line)[i + name_len] != '\"'
				&& (*line)[i + name_len] != '\n'
				&& (*line)[i + name_len] != ' ')
				name_len++;
			*line = here_doc_expand_aux(line, name_len, &i);
		}
		i++;
	}
	return (*line);
}

static void	here_doc_child(char *end_of_input, int here_pipe[])
{
	char	*str;
	char	*aux;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, sig_here_doc);
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
	close(here_pipe[PIPE_RD]);
	write(here_pipe[PIPE_WR], str, ft_strlen(str));
	close(here_pipe[PIPE_WR]);
}

int	here_doc(char *end_of_input)
{
	int		here_pipe[2];

	if (pipe(here_pipe) == -1)
		return (-1);
	if (fork() == 0)
	{
		here_doc_child(end_of_input, here_pipe);
		exit(0);
	}
	wait(NULL);
	close(here_pipe[PIPE_WR]);
	return (here_pipe[PIPE_RD]);
}

int	is_last_redir(t_redir *next, enum e_token_type type1,
	enum e_token_type type2)
{
	while (next && next->type != type1 && next->type != type2)
		next = next->next;
	if (next)
		return (0);
	return (1);
}
